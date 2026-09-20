//
// Created by tv on 04.11.23.
//
#include"silverlightmatchmaking.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    SilverlightMatchmaking::SilverlightMatchmaking() {
        this->patch = {
            {0x021652ac, PatchElement("li r3, 1000", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x0216884c, 0x021652ac))},
        };
    }

    bool SilverlightMatchmaking::isCheatModule() {
        return false;
    }

	std::vector<const char*> SilverlightMatchmaking::incompatibleModules() {
		return {"AntiMMR"};
	}

    REGISTERVCLASS(SilverlightMatchmaking)
}
