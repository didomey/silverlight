//
// Created by tv on 04.11.23.
//
#include"shopbypass.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    ShopBypass::ShopBypass() {
        this->patch = {
			{0x02847f50, PatchElement("li r3, 0x1", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x028c2248, 0x02847f50))},
			{0x02847f94, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) 0x02847fa8, 0x02847f94), DynamicBranchReplacementSingle(BranchType::BranchIfGreaterThan, (void*) 0x02847fa8, 0x02847f94))}
		};
		this->enablePatch();
    }

    bool ShopBypass::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(ShopBypass)
}
