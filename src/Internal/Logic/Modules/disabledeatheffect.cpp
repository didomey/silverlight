//
// Created by tv on 04.11.23.
//
#include"disabledeatheffect.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

bool repl_shouldRenderDeathEffect() {
	return false;
}

namespace Modules {
    DisableDeathEffect::DisableDeathEffect() {
        this->patch = {
                {0x026c03d0, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) repl_shouldRenderDeathEffect, 0x026c03d0), "lwz r12, 0x34(r3)")},
				// Below fix the side effects
                {0x026c0a74, PatchElement("li r3, 1", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x026c03d0, 0x026c0a74))},
        };
    }

    bool DisableDeathEffect::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DisableDeathEffect)
}
