//
// Created by tv on 04.11.23.
//
#include"noautocameramovement.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    InvalidGearCrashFix::InvalidGearCrashFix() {
        this->patch = {
                {0x02664f20, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02057c74, 0x02664f20))},
                {0x0269D170, PatchElement("li r12, 1", "li r12, 0xec(r12)")},
        };
        this->enablePatch();
    }

    bool InvalidGearCrashFix::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(InvalidGearCrashFix)
}
