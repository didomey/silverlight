//
// Created by tv on 04.11.23.
//
#include"forcelag.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    ForceLag::ForceLag() {
        this->patch = {
                {0x0266A420, PatchElement("li r12, 255", "lwz r12, 0x0(r3)")},
        };
    }

    bool ForceLag::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(ForceLag)
}
