//
// Created by tv on 04.11.23.
//
#include"noinktank.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    NoInkTank::NoInkTank() {
        this->patch = {
			{0x026d5218, PatchElement("blr", "mflr r0")},
			{0x0219A72C, PatchElement("li r3, 0", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x0219f188, 0x0219a72c))}
		};
    }

    bool NoInkTank::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(NoInkTank)
}
