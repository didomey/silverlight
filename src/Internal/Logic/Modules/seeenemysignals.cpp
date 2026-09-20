//
// Created by tv on 04.11.23.
//
#include"seeenemysignals.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    SeeEnemySignals::SeeEnemySignals() {
        this->patch = {
                {0x02407DA4, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x02407ee8, 0x02407DA4))},
                {0x0240809C, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x024081c0, 0x0240809C))},
        };
    }

    bool SeeEnemySignals::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(SeeEnemySignals)
}
