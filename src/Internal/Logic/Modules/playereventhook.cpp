//
// Created by tv on 04.11.23.
//
#include"playereventhook.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>
#include "Game/MainMgrBase.h"
#include "Game/PlayerClone.h"
#include "Internal/silverlight.h"

#define DEBUG_LOG

PlayerNetState prevPlayerNetStates[8] = {};
PlayerNetState playerNetStates[8] = {};

void repl_unpackStateEvent(Game::Player::Player* player, Game::PlayerCloneHandle::PlayerCloneObj* event, uint32_t* cloneHandleIdx) {
#ifdef DEBUG_LOG
	uint32_t playerIdx = Game::Utl::getPlayerIdx(player);
	/*
	static uint8_t eventIdBuf[8] = {};
	static uint32_t eventIdBufIdx = -1;

	eventIdBufIdx++;

	if (eventIdBufIdx > 7) eventIdBufIdx = 0;

	eventIdBuf[eventIdBufIdx] = event->eventId;

	std::string eventBufStr = {};

	for (uint32_t i = 0; i < 8; i++) {
		uint8_t curEventId = eventIdBuf[i];
		eventBufStr.append(std::to_string(curEventId) + ", ");
	}

	eventBufStr.pop_back();
	eventBufStr.pop_back();

	std::string text = "Events: " + eventBufStr;
    silverlightInstance->m_renderer.setTextCursor({-(text.length() * 9.600006 / 2), 0});
    silverlightInstance->m_renderer.drawText(text);
	*/
#endif

	uint32_t localPlayerIdx = Game::Utl::getPlayerIdx(player);

	PlayerNetState* playerNetState = &playerNetStates[localPlayerIdx];
	
	prevPlayerNetStates[localPlayerIdx] = *playerNetState;

	uint8_t eventId = event->eventId;

	auto now = std::chrono::high_resolution_clock::now();

	if (eventId >= 0 && eventId <= 2) {
		playerNetState->isRevived = false;
	}
	else if (eventId == 3) {
		playerNetState->isRevived = true;
		playerNetState->lastReviveTime = now;
	}
	else if (eventId == 5) {
		playerNetState->dokanWarpActive = true;
	}
	else if (eventId == 7) {
		playerNetState->dokanWarpActive = false;
	}

	Game::PlayerCloneHandle::unpackStateEvent(player, event, cloneHandleIdx);
}

namespace Modules {
    PlayerEventHook::PlayerEventHook() {
		auto now = std::chrono::high_resolution_clock::now();

		for (uint32_t i = 0; i < 8; i++) {
			PlayerNetState playerNetState = PlayerNetState { .isRevived = true, .lastReviveTime = now, .dokanWarpActive = true, .lastDokanWarpUpdateTime = now};
			playerNetStates[i] = playerNetState;
			prevPlayerNetStates[i] = playerNetState;
		}

        this->patch = {
            {0x0266b924, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_unpackStateEvent, 0x0266b924), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x0266aef0, 0x0266b924))},
            {0x0266b934, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_unpackStateEvent, 0x0266b934), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x0266aef0, 0x0266b934))},
        };
        this->enablePatch();
    }

    bool PlayerEventHook::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(PlayerEventHook)
}
