//
// Created by tv on 04.11.23.
//
#include"changeskybox.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include"Game/skybox.h"
#include"Game/match.h"
#include "Game/savedatavss.h"
#include "InputModule.h"
#include "Internal/silverlight.h"

FUNCBIND(setEnv, 0242b41c, uint32_t(*)(uint32_t* param_1, const char* envName))

void repl_setEnv(uint32_t* param_1, const char* envName) {
	Modules::ChangeSkyboxInput *changeSkyboxInputModule = silverlightInstance->m_moduleStates.getModule<Modules::ChangeSkyboxInput>();
	setEnv(param_1, changeSkyboxInputModule->skybox.c_str());
	return;
}

namespace Modules {
	void ChangeSkyboxInput::receivedEntry(const std::u16string &input) {
		SkyboxInfo &closestMatch = findClosestMatch<SkyboxInfo>(u16string_to_string(input), skyboxes,
            [](const SkyboxInfo &info) -> std::string {
            return info.name;
    	});

		this->skybox = closestMatch.internalName;
	}


	REGISTERVCLASS(ChangeSkyboxInput)

    ChangeSkybox::ChangeSkybox() {
        this->patch = {
			{0x0242952c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setEnv, 0x0242952c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setEnv, 0x0242952c))},
			{0x024295fc, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setEnv, 0x024295fc), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setEnv, 0x024295fc))},
			{0x024296bc, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setEnv, 0x024296bc), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setEnv, 0x024296bc))},
			{0x0242972c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setEnv, 0x0242972c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setEnv, 0x0242972c))},
			{0x02429760, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setEnv, 0x02429760), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setEnv, 0x02429760))},
			{0x02429814, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setEnv, 0x02429814), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setEnv, 0x02429814))},
			{0x02429880, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setEnv, 0x02429880), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setEnv, 0x02429880))},
			{0x024298b0, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setEnv, 0x024298b0), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setEnv, 0x024298b0))},
			{0x024298dc, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setEnv, 0x024298dc), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setEnv, 0x024298dc))},
			{0x02429918, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setEnv, 0x02429918), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setEnv, 0x02429918))},
			{0x02429a8c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setEnv, 0x02429a8c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setEnv, 0x02429a8c))},
			{0x02429ac4, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setEnv, 0x02429ac4), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setEnv, 0x02429ac4))},
			{0x02429b90, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setEnv, 0x02429b90), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setEnv, 0x02429b90))},
        };
    }

    bool ChangeSkybox::isCheatModule() {
        return false;
    }

	std::string ChangeSkybox::helpText() {
		std::string skyboxesStr = {};

		for (const auto& skybox : skyboxes) {
			skyboxesStr.append(skybox.name + ",");
		}

		skyboxesStr.pop_back();

		return "Available Skyboxes: " + skyboxesStr;
	}

    REGISTERVCLASS(ChangeSkybox)
}
