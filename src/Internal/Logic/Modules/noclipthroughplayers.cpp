//
// Created by tv on 04.11.23.
//
#include"noclipthroughplayers.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    NoclipThroughPlayers::NoclipThroughPlayers() {
        this->patch = {
                {0x02650138, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x0267f840, 0x02650138))}
        };
    }

    bool NoclipThroughPlayers::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(NoclipThroughPlayers)
}
