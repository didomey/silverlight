//
// Created by tv on 04.11.23.
//
#include"debugmove.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

bool repl_isInDebugMove_UpDown() {
	return true;
}

namespace Modules {
    DebugMove::DebugMove() {
        this->patch = {
                {0x0263d180, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) repl_isInDebugMove_UpDown, 0x0263d180), "li r3, 0")},
        };
    }

    bool DebugMove::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(DebugMove)
}
