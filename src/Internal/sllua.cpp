#include "Internal/silverlight.h"
#include "sllua.h"
#include "Game/Filetypes/Helpers/Filesystem.cpp"

extern "C" {
#include <lua.h>
}

#define LUA_PREFIX "[Lua] "

namespace LuaAPI {
	static int cafePrint() {
		int n = lua_gettop(L);

		std::string textForPrint = {};

    	for (int i = 1; i <= n; ++i) {
			if (!lua_isnumber(L, i)) {
				return luaL_error(L, "Argument %d is not a string", i);
			}

			textForPrint.append(std::to_string(lua_tostring(L, i)));
    	}

		lua_pushinteger(this->L, result);

		return 0;
	}
}

Lua::Lua() {
	this->L = lua_newstate();
}

void Lua::initLua() {
	luaL_openlibs(this->L);

	lua_pushcfunction(this->L, cafePrint); // Push the function onto the stack
	lua_setglobal(this->L, "cafePrint");

	std::vector<std::string> luaFilePaths = Filesystem::listFileDir("vol/content/lua");

	for (const auto& filePath : luaFilePaths) {
		std::string luaFile = readFile(filePath);			

		handleLuaFile(luaFile);
	}
}

void Lua::handleLuaFile(std::string path) {
	int r = luaL_dofile(this->L, path);

	this->checkLua(r);
	
	int startRef = loadLuaFunc("start");
	int updateRef = loadLuaFunc("update");
	int stopRef = loadLuaFunc("stop");

	Modules::LuaDynamicModule module = Modules::LuaDynamicModule { .startRef = startRef, .updateRef = updateRef, .stopRef = stopRef };

	this->modules.push_back(module);
}

int Lua::loadLuaFunc(std::string name) {
	int r = lua_getglobal(L, name);

	this->checkLua(r);

	if (!lua_isfunction(this->L, -1)) {
		CAFECRASH(LUA_PREFIX + "\"" + name + "\" is not a function.");
		lua_pop(this->L, 1);
		return { nullptr, 0 };
	}

	int ref = luaL_ref(this->L, LUA_REGISTRYINDEX);

	return ref;
}
