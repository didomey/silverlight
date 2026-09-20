//
// Created by tv on 04.11.23.
//
#include"lightgfxmode.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    LightGfxMode::LightGfxMode() {
        this->patch = {
            {0x0242a124, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchIfEqual, (void*) 0x0242a17c, 0x02664f20))},
            {0x0242a130, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchIfEqual, (void*) 0x0242a17c, 0x02664f20))},
        };
    }

    bool LightGfxMode::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(LightGfxMode)
}
