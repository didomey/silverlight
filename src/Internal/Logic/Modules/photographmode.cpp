//
// Created by tv on 04.11.23.
//
#include"photographmode.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include "Internal/silverlight.h"

namespace Modules {
    PhotographModePatch::PhotographModePatch() {
        this->patch = {
            {0x020777b8, PatchElement("blr", "lis r12, 0x1001")},
			// Causes some weapons to break
			//{0x02634fac, PatchElement("li r31, 0", "li r31, 1")}


            {0x026421ec, PatchElement("li r3, 0", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02634f54, 0x026421ec))},
            {0x02659e24, PatchElement("li r3, 0", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02634f54, 0x02659e24))},

        };
    }

    bool PhotographModePatch::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(PhotographModePatch)

	bool PhotographModeUpdate::requireRenderFocus() {
		return true;
	}

	void PhotographModeUpdate::start() {
    }

    void PhotographModeUpdate::stop() {
    }

    void PhotographModeUpdate::update(float deltaTime) {
    }

    bool PhotographModeUpdate::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(PhotographModeUpdate)

	void PhotographModeWrapper::start() {
		PhotographModeUpdate *photographUpdateModule = silverlightInstance->m_moduleStates.getModule<PhotographModeUpdate>();
		PhotographModePatch *photographPatchModule = silverlightInstance->m_moduleStates.getModule<PhotographModePatch>();

		photographUpdateModule->enable();
		photographPatchModule->enablePatch();
    }

    void PhotographModeWrapper::stop() {
		PhotographModeUpdate *photographUpdateModule = silverlightInstance->m_moduleStates.getModule<PhotographModeUpdate>();
		PhotographModePatch *photographPatchModule = silverlightInstance->m_moduleStates.getModule<PhotographModePatch>();

		photographUpdateModule->disable();
		photographPatchModule->disablePatch();
    }

    void PhotographModeWrapper::update(float deltaTime) {
    }

    bool PhotographModeWrapper::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(PhotographModeWrapper)
}
