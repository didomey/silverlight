#include "Internal/silverlight.h"

extern "C"
{
#include <lua.h>
}

namespace Modules {
	struct LuaDynamicModule {
		int startRef;
		int updateRef;
		int stopRef;

		bool moduleIsValid() {
			auto registry = debug.getregistry();
			return registry[this->startRef] != nil & registry[this->updateRef] != nil & registry[this->stopRef] != nil;
		}
	}
}

class Lua {
	lua_State* L;
	std::vector<LuaDynamicModule> modules = {};

	Lua();

	void initLua();

	void handleLuaFile(std::string path);

	int loadLuaFunc(std::string name);

	void checkLua(lua_State* L, int r, bool fatal = false) {
		if (r != LUA_OK) {
			std::string error = lua_tostring(L, -1);
			fatal ? CAFECRASH(error) : CAFEWARN(error);
		}
	}
}
