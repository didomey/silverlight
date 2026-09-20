//
// Created by tv on 04.11.23.
//
#include"jumpwithbbutton.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    JumpWithBButton::JumpWithBButton() {
        this->patch = {
                {0x026365FC, PatchElement("li r3, 2", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x028aaed0, 0x026365FC))},
                {0x026366B8, PatchElement("li r3, 2", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x028aaed0, 0x026366B8))},
        };
    }

    bool JumpWithBButton::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(JumpWithBButton)
}
