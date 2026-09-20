//
// Created by tv on 04.11.23.
//
#include"plazaplayersalwaysvisible.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    PlazaPlayersAlwaysVisible::PlazaPlayersAlwaysVisible() {
        this->patch = {
                {0x026dd9cc, PatchElement("li r3, 0", "mflr r0")},
                {0x026dd9d0, PatchElement("blr", "stwu r1, -0x10(r1)")},
        };
    }

    bool PlazaPlayersAlwaysVisible::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(PlazaPlayersAlwaysVisible)
}
