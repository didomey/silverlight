//
// Created by tv on 04.11.23.
//
#include"fastinternet.h"
#include "forcelag.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include "Internal/silverlight.h"

namespace Modules {
    FastInternetPatch::FastInternetPatch() {
        this->patch = {
            {0x0266A420, PatchElement("li r12, 0", "lwz r12, 0x0(r3)")},
        };
    }

    bool FastInternetPatch::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(FastInternetPatch)

	FastInternetWrapper::FastInternetWrapper() {
	}

    void FastInternetWrapper::start() {
		FastInternetPatch *fastInternetPatchModule = silverlightInstance->m_moduleStates.getModule<FastInternetPatch>();
		ForceLag *forceLagModule = silverlightInstance->m_moduleStates.getModule<ForceLag>();

		forceLagModule->disablePatch();
		fastInternetPatchModule->enablePatch();
    }

    void FastInternetWrapper::stop() {
		FastInternetPatch *fastInternetPatchModule = silverlightInstance->m_moduleStates.getModule<FastInternetPatch>();

		fastInternetPatchModule->disablePatch();
	}

    void FastInternetWrapper::update(float deltaTime) {
    }

    bool FastInternetWrapper::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(FastInternetWrapper)
}
