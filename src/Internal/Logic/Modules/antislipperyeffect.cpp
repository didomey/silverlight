//
// Created by tv on 04.11.23.
//
#include"antislipperyeffect.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    AntiSlipperyEffect::AntiSlipperyEffect() {
        this->patch = {
                {0x0264E0C4, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) 0x0264e114, 0x0264E0C4), DynamicBranchReplacementSingle(BranchType::BranchIfLessThan, (void*) 0x0264e114, 0x0264E0C4))},
                {0x0264E1B4, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) 0x0264E1C0, 0x0264E1B4), "stfs f8, 0x490(r31)")},
                {0x0264E1B4, PatchElement("li r7, 9", "lwz r7, 0x310(r31)")},
                {0x0264776C, PatchElement("nop", "stfs f0, 0x45c(r31)")},
                {0x0263DA64, PatchElement("nop", "stfs f30, 0x45c(r31)")},
        };
    }

    bool AntiSlipperyEffect::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AntiSlipperyEffect)
}
