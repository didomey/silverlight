//
// Created by tv on 04.11.23.
//
#include"disablejumprng.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    DisableJumpRNG::DisableJumpRNG() {
        this->patch = {{0x026a6aa0, PatchElement("nop", "stw r3, 0x264(r31)")}};
    }

    bool DisableJumpRNG::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(DisableJumpRNG)
}
