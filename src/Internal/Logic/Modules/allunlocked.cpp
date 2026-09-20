//
// Created by tv on 04.11.23.
//
#include"allunlocked.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

bool repl_isHaveGear(uint32_t* _this, uint32_t* param_1, int32_t param_2, int32_t param_3) {
	return true;
}

bool repl_isHaveWeapon(uint32_t* _this, int32_t param_1, int32_t param_2) {
	return true;
}

namespace Modules {
    AllUnlocked::AllUnlocked() {
        this->patch = {
                {0x021ae2f8, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) repl_isHaveGear, 0x021ae2f8), "mflr r0")},
                {0x021ae40c, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) repl_isHaveWeapon, 0x021ae40c), "mflr r0")},
        };
        this->enablePatch();
    }

    bool AllUnlocked::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(AllUnlocked)
}
