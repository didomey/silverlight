//
// Created by tv on 04.11.23.
//
#include"extendedleavethreshold.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    ExtendedLeaveThreshold::ExtendedLeaveThreshold() {
        this->patch = {
                {0x0274be78, PatchElement("li r3, 100", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x027565fc, 0x0274be78))},
        };
        //this->enablePatch();
    }

    bool ExtendedLeaveThreshold::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(ExtendedLeaveThreshold)
}
