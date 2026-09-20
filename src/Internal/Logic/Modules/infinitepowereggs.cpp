//
// Created by tv on 04.11.23.
//
#include"infinitepowereggs.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    InfinitePowerEggs::InfinitePowerEggs() {
        this->patch = {{0x0246f84c, PatchElement("li r3, 9999", "lwz r3, 0x240(r3)")}};
    }

    bool InfinitePowerEggs::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(InfinitePowerEggs)
}
