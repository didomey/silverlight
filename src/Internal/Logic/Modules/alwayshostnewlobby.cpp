//
// Created by tv on 04.11.23.
//
#include"alwayshostnewlobby.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    AlwaysHostNewLobby::AlwaysHostNewLobby() {
        this->patch = {
			{0x02165458, PatchElement("li r0, 3", "li r0, 2")},
        };
    }

    bool AlwaysHostNewLobby::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(AlwaysHostNewLobby)
}
