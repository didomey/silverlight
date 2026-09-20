//
// Created by tv on 04.11.23.
//
#include"jumpmidair.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    JumpMidair::JumpMidair() {
        this->patch = {
                {0x0263D6A8, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) 0x0263D6B0, 0x0263D6A8), DynamicBranchReplacementSingle(BranchType::BranchIfGreaterThan, (void*) 0x0263D6B0, 0x0263D6A8))},
                {0x0263D3D4, PatchElement("li r11, 0", "lwz r11, 0x5c8(r31)")},
                {0x0264BE84, PatchElement("li r10, 0", "lwz r10, 0x5d8(r31)")},
                {0x0263D99C, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchIfLessThan, (void*) 0x0263de00, 0x0263D99C))},
        };
    }

    bool JumpMidair::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(JumpMidair)
}
