//
// Created by tv on 04.11.23.
//
#include"instarespawn.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    InstaRespawn::InstaRespawn() {
        this->patch = {
			{0x02634144, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x02634158, 0x02634144))},
            {0x026341c8, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x02634240, 0x026341c8))},
        };
    }

    bool InstaRespawn::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(InstaRespawn)
}
