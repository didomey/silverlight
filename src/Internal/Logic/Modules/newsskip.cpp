//
// Created by tv on 04.11.23.
//
#include"newsskip.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    NewsSkip::NewsSkip() {
        this->patch = {
			{0x026dd024, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x028c2248, 0x026dd024))}
		};
		this->enablePatch();
    }

    bool NewsSkip::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(NewsSkip)
}
