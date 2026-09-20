//
// Created by tv on 04.11.23.
//
#include"disablebattlemusic.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include <coreinit/memory.h>

namespace Modules {
    DisableBattleMusic::DisableBattleMusic() {
        this->patch = {
                {0x021e8174, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) OSBlockMove, 0x021e8174))},
        };
    }

    bool DisableBattleMusic::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DisableBattleMusic)
}
