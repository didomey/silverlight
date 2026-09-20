//
// Created by tv on 04.11.23.
//
#include"disableshotguide.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    DisableShotGuide::DisableShotGuide() {
        this->patch = {
                {0x026421ec, PatchElement("li r3, 0", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02634f54, 0x026421ec))},
        };
    }

    bool DisableShotGuide::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DisableShotGuide)
}
