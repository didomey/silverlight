//
// Created by tv on 04.11.23.
//
#include"disablevisiblegear.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    DisableVisibleGear::DisableVisibleGear() {
        this->patch = {
                {0x02903aac, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02902c7c, 0x02903aac))},
        };
    }

    bool DisableVisibleGear::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DisableVisibleGear)
}
