//
// Created by tv on 04.11.23.
//
#include"lowgravity.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>
#include "Game/Player.h"

bool repl_Player_isJumpOverZero(Game::Player::Player* _this) {
	return true;
}

namespace Modules {
    LowGravity::LowGravity() {
        this->patch = {
                {0x026316dc, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) repl_Player_isJumpOverZero, 0x026316dc), "lis r12, 0x100f")},
        };
    }

    bool LowGravity::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(LowGravity)
}
