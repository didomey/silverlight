//
// Created by tv on 04.11.23.
//
#include"spambooyahsignal.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    SpamBooyahSignal::SpamBooyahSignal() {
        this->patch = {
			{0x02408200, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchIfEqual, (void*) 0x02408260, 0x02408200))}
        };
    }

    bool SpamBooyahSignal::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(SpamBooyahSignal)
}
