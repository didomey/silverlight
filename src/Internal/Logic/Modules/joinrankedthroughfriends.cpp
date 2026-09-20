//
// Created by tv on 04.11.23.
//
#include"joinrankedthroughfriends.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    JoinRankedThroughFriends::JoinRankedThroughFriends() {
        this->patch = {
                {0x027F67A8, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x027f67bc, 0x027F67A8))},
        };
    }

    bool JoinRankedThroughFriends::isCheatModule() {
        return false;
    }

	std::string JoinRankedThroughFriends::helpText() {
		return "Replaces the ranked battle button with join through friend functionality. Disable if you want to queue normally.";
	}

    REGISTERVCLASS(JoinRankedThroughFriends)
}
