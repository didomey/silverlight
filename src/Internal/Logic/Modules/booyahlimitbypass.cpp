//
// Created by tv on 04.11.23.
//
#include"booyahlimitbypass.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    BooyahLimitBypass::BooyahLimitBypass() {
        this->patch = {
                {0x02407b84, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchIfGreaterThan, (void*) 0x02407c40, 0x02407b84))},
        };
    }

    bool BooyahLimitBypass::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(BooyahLimitBypass)
}
