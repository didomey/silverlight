//
// Created by tv on 04.11.23.
//
#include"disableplayershadows.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include <coreinit/memory.h>

namespace Modules {
    DisablePlayerShadows::DisablePlayerShadows() {
        this->patch = {
                {0x02db15e0, PatchElement("blr", "stwu r1, -0x5f0(r1)")},
        };
    }

    bool DisablePlayerShadows::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DisablePlayerShadows)
}
