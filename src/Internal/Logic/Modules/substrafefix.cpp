//
// Created by tv on 04.11.23.
//
#include"substrafefix.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>
#include "Game/PlayerInkAction.h"
#include "Game/Player.h"

void repl_calcShot(uint32_t* _this, int isFirstAnimFrame) {
	if (!Game::Player::localInstance) {
		Game::PlayerInkAction::calcShot(_this, isFirstAnimFrame);
		return;
	}

	if ((Game::Player::localInstance->subWeaponId == 3 || Game::Player::localInstance->subWeaponId == 5) && Game::Player::localInstance->isSubWeaponHeld == 1) {
		isFirstAnimFrame = 0;
	}

	Game::PlayerInkAction::calcShot(_this, isFirstAnimFrame);
}

namespace Modules {
    SubStrafeFix::SubStrafeFix() {
        this->patch = {
            {0x02650bb4, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_calcShot, 0x02650bb4), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::PlayerInkAction::calcShot, 0x02650bb4))},
        };
    }

    bool SubStrafeFix::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(SubStrafeFix)
}
