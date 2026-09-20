//
// Created by tv on 04.11.23.
//
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

#include "allteammatesinvincible.h"

FUNCBINDUNK(02635078, int(*)(int param_1, uint param_2));

int32_t repl_LAB_02635078(int param_1, uint param_2) {
	return 100000000;
}

namespace Modules {
    AllTeammatesInvinciblePatch::AllTeammatesInvinciblePatch() {
        this->patch = {
			{0x02635078, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) repl_LAB_02635078, 0x02635078), "li r3, 0x168")}
		};
    }

    bool AllTeammatesInvinciblePatch::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AllTeammatesInvinciblePatch)
}
