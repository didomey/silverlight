//
// Created by tv on 04.11.23.
//
#include"infinitelives.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    InfiniteLives::InfiniteLives() {
        this->patch = {{0x025fd18c, PatchElement("nop", "addic. r0, r11, -1")}};
    }

    bool InfiniteLives::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(InfiniteLives)
}
