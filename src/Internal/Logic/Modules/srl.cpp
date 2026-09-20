//
// Created by tv on 04.11.23.
//
#include"srl.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include "Game/savedatavss.h"

Gear* repl_getCommonPlayerGearId(uint32_t* param_1, uint32_t* param_2) {
	static Gear gear = Gear { 0x733D, 0x733D, 0x733D, 0, 0, 0, 0 };
	return &gear;
}

namespace Modules {
    SRL::SRL() {
        this->patch = {
				{0x021a93cc, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_getCommonPlayerGearId, 0x021a93cc), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) getCommonPlayerGearId, 0x021a93cc))},

        };
    }

    bool SRL::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(SRL)
}
