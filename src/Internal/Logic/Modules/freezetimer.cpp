//
// Created by tv on 04.11.23.
//
#include"freezetimer.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    FreezeTimer::FreezeTimer() {
        this->patch = {{0x02150b84, PatchElement("nop", "subi r0, r12, 0x1")}};
    }

    bool FreezeTimer::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(FreezeTimer)
}
