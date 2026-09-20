//
// Created by tv on 04.11.23.
//
#include"endgame.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include "Game/RefereeVersus.h"

static Game::RefereeVersus::RefereeVersus* refereeVersus = nullptr;

void repl_LAB_0274c450(Game::RefereeVersus::RefereeVersus* _this) {
	refereeVersus = _this;
}

namespace Modules {
	void skipIntro() {
		refereeVersus->intro = 0;
	}

	void endGame() {
		refereeVersus->endGame = 1;
	}

    EndGameHook::EndGameHook() {
        this->patch = {
                {0x0274c450, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) repl_LAB_0274c450, 0x0274c450), "stwu r1, -0x28(r1)")},
        };
        this->enablePatch();
    }

    bool EndGameHook::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(EndGameHook)
}
