//
// Created by tv on 04.11.23.
//
#include"signalsalwaysenabled.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    SignalsAlwaysEnabled::SignalsAlwaysEnabled() {
        this->patch = {
                {0x024CB2FC, PatchElement("li r3, 1", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x024cb234, 0x024cb2fc))},
                {0x024CB268, PatchElement("li r3, 1", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x024cb234, 0x024cb268))},
        };
    }

    bool SignalsAlwaysEnabled::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(SignalsAlwaysEnabled)
}
