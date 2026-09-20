//
// Created by tv on 04.11.23.
//
#include"matchparamshook.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>
#include "Game/MainMgrBase.h"
#include "Game/PlayerClone.h"
#include "Internal/silverlight.h"


namespace Modules {
    MatchParamsHook::MatchParamsHook() {
        this->patch = {
            //{0x0266b924, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_unpackStateEvent, 0x0266b924), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x0266aef0, 0x0266b924))},
            //{0x0266b934, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_unpackStateEvent, 0x0266b934), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x0266aef0, 0x0266b934))},
        };
        this->enablePatch();
    }

    bool MatchParamsHook::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(MatchParamsHook)
}
