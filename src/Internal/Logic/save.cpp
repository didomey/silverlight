#include "Game/Filetypes/Helpers/Filesystem.h"

#include "Internal/silverlight.h"
#include <fstream>
#include<Shared/Core/Assert.h>
#include<unordered_set>
#include<string>
#include "Shared/crypto.h"

std::unordered_set<std::string_view> g_untoggleableModules = {
    "ShowCopyrightText",
    "CheatIndicator",
	"PhotographModeWrapper",
	"PhotographModeUpdate",
	"PhotographModePatch",
};

std::vector<std::string_view> splitString(std::string_view str, const std::initializer_list<char> &delimiters) {
    std::vector<std::string_view> out;

    out.reserve(str.size() / 4);

    size_t beginCurSegment = 0;
    size_t endCurSegment = 0;

    while(endCurSegment <= str.length()) {
        if(std::ranges::any_of(delimiters,[&](char c) -> bool{
            return c == str[endCurSegment+1];
        })) {
            out.push_back(str.substr(beginCurSegment,endCurSegment + 1 - beginCurSegment));
            beginCurSegment = endCurSegment + 2;
            endCurSegment += 2;
            continue;
        }

        endCurSegment++;
    }

    if(beginCurSegment != endCurSegment) {
        out.push_back(str.substr(beginCurSegment,endCurSegment - 1 - beginCurSegment));
    };

    if(out.back().empty())
        out.erase(out.end()--);
    //out.shrink_to_fit();

    return out;
}

std::vector<std::pair<std::string_view,bool>> readCSVModuleStateMap(std::string_view string) {
    std::vector<std::pair<std::string_view,bool>> out;



    std::vector<std::string_view> data = splitString(string,{' ',',','\n','\t','\v'});

    if(data.size() < 2)
        return out;

    CAFEASSERT(data.size() % 2 == 0)

    for(auto iter = data.begin(); iter != data.end(); iter++){
        std::string_view str = *iter;
        iter++;
        if(iter == data.end())
            break;
        out.emplace_back(str, (*iter == "1"));
    }

    return out;
}

std::string generateCSVModuleStateMap(std::vector<std::pair<std::string_view,bool>> data){
   std::string str;
   for(auto elem: data){
       str += elem.first;
       str += ",";
       str += std::to_string(elem.second);
       str += "\n";
   }

    return str;
}

void saveModules() {
    std::vector<std::pair<std::string_view, bool>> moduleStates;

	for (const auto& module : silverlightInstance->m_moduleStates.m_updateModules) {
		moduleStates.push_back({module->getModuleName(),module->m_enabled});
	}
    for (const auto& module : silverlightInstance->m_moduleStates.m_patchModules) {
        moduleStates.push_back({module->getModuleName(),module->m_enabled});
    }


    std::string config = generateCSVModuleStateMap(moduleStates);
	// Encrypt
	std::string key = "S55rKVr5EogxgKmj";
	xor_crypt(key, config);

    Filesystem::writeFile("/vol/save/slModState", std::span<uint8_t>((uint8_t*)config.data(), (uint8_t*)config.data() + config.length()));
}

void loadModules() {
    std::vector<uint8_t> encryptedConfigBytes = Filesystem::readFile("/vol/save/slModState");

	std::string encryptedConfigBytesStr(encryptedConfigBytes.begin(), encryptedConfigBytes.end());
	// Decrypt
	std::string key = "S55rKVr5EogxgKmj";
	xor_crypt(key, encryptedConfigBytesStr);

	std::vector<uint8_t> configBytes(encryptedConfigBytesStr.begin(), encryptedConfigBytesStr.end());
    configBytes.push_back(0);

    std::vector<std::pair<std::string_view, bool>> moduleStates = readCSVModuleStateMap((char*)(configBytes.data()));

    for(auto state: moduleStates) {

        if(g_untoggleableModules.contains(state.first))
            continue;

        auto uMod = std::ranges::find_if(silverlightInstance->m_moduleStates.m_updateModules,
                                           [&](auto& mod) -> bool {
                                               return state.first == mod->getModuleName();
                                           });

        auto pMod = std::ranges::find_if(silverlightInstance->m_moduleStates.m_patchModules,
                                           [&](auto& mod) -> bool {
                                               return state.first == mod->getModuleName();
                                           });

        if (uMod != silverlightInstance->m_moduleStates.m_updateModules.end()) {
            if((*uMod)->m_enabled != state.second)
                (*uMod)->toggle();
        } else if (pMod != silverlightInstance->m_moduleStates.m_patchModules.end()) {
            if((*pMod)->m_enabled != state.second)
                (*pMod)->toggle();
        }
    }
}

