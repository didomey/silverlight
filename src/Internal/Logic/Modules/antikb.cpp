//
// Created by tv on 04.11.23.
//
#include"antikb.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    AntiKB::AntiKB() {
        this->patch = {
                {0x02647E00, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) 0x02647E78, 0x02647E00), "lfs f8, 0x8(r1)")},
                {0x02648034, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) 0x02648060, 0x02648034), DynamicBranchReplacementSingle(BranchType::BranchIfGreaterThan, (void*) 0x02648060, 0x02648034))},
				{0x0256d1ac, PatchElement("blr", "mflr r0")}
        };
    }

    bool AntiKB::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AntiKB)
}
