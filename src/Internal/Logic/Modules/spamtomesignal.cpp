//
// Created by tv on 04.11.23.
//
#include"spamtomesignal.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    SpamToMeSignal::SpamToMeSignal() {
        this->patch = {
			{0x02407fd0, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchIfEqual, (void*) 0x02408030, 0x02407fd0))}
        };
    }

    bool SpamToMeSignal::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(SpamToMeSignal)
}
