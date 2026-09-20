//
// Created by tv on 04.11.23.
//
#include"aimbot.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/mat3x3.hpp>
#include<Shared/Cafe/vpad.h>
#include "Game/MainMgrBase.h"
#include "glm/gtx/string_cast.hpp"
#include "playereventhook.h"
#include "Internal/silverlight.h"

bool repl_checkInPreRevival_NoControl() {
	return true;
}

namespace Modules {

    void AimBotUpdate::start() {
    }

    void AimBotUpdate::stop() {
    }

    void AimBotUpdate::update(float deltaTime) {
		Game::Player::Player** players = Game::MainMgrBase::sInstance->playerMgr->factories->playerFactoryIdx->playerActors;
		uint32_t playerCount = Game::MainMgrBase::sInstance->playerMgr->factories->playerFactoryIdx->maxPlayerCount;

		if (playerCount < 2) return;

		Game::Player::Player* localPlayer = Game::Player::localInstance;

		//if (!localPlayer->isShooting) return;

		glm::vec2 localPlayerHorizontalVec = {localPlayer->position.x, localPlayer->position.z};

		std::vector<Game::Player::Player*> remotePlayers = {};

		for (uint32_t i = 0; i < playerCount; i++) {
			Game::Player::Player* curPlayer = players[i];

			if (!curPlayer) continue;
			if (curPlayer != localPlayer) remotePlayers.push_back(curPlayer);
		}

		Game::Player::Player* closestPlayer = nullptr;
		float closestPlayerDist;

		for (const auto& remotePlayer : remotePlayers) {
			glm::vec2 remotePlayerHorizontalVec = {remotePlayer->position.x, remotePlayer->position.z};
			float remotePlayerDist = glm::distance(localPlayerHorizontalVec, remotePlayerHorizontalVec);

			if (remotePlayer->teamId == localPlayer->teamId) continue;

			uint32_t remotePlayerIdx = Game::Utl::getPlayerIdx(remotePlayer);
			PlayerNetState remotePlayerNetState = playerNetStates[remotePlayerIdx];

			if (!remotePlayerNetState.isRevived) continue;

			if (!closestPlayer || remotePlayerDist < closestPlayerDist) {
				closestPlayer = remotePlayer;
				closestPlayerDist = remotePlayerDist;
			}
		}

		if (!closestPlayer) return;
		
		this->closestPlayer = closestPlayer;
		this->closestPlayerDist = closestPlayerDist;

		glm::vec3 localPlayerPosition = localPlayer->position;
		
		//localPlayerPosition.x -= 0.1;
		//localPlayerPosition.x -= 1.0;


		glm::vec3 dir = glm::normalize(closestPlayer->position - localPlayerPosition);

		if (Game::Player::isInSquid(closestPlayer)) {
			dir.y -= 0.05;
		}

		localPlayer->playerBehindCamera->pitch = dir;
		localPlayer->playerBehindCamera->yaw = dir;
    }

	void AimBotUpdate::render(float deltaTime) {
		if (this->closestPlayer) {
			std::string text = "Target Player: " + std::to_string(Game::Utl::getPlayerIdx(this->closestPlayer));
			silverlightInstance->m_renderer.setTextCursor({-(text.length() * 9.600006 / 2), 300});
			silverlightInstance->m_renderer.drawText(text);
		}
		std::string text = "Closest Player Dist: " + to_string_with_precision(this->closestPlayerDist);
        silverlightInstance->m_renderer.setTextCursor({-(text.length() * 9.600006 / 2), 325});
        silverlightInstance->m_renderer.drawText(text);
	}

    bool AimBotUpdate::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AimBotUpdate)

    AimBotPatch::AimBotPatch() {
        this->patch = {
            {0x026351c0, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_checkInPreRevival_NoControl, 0x026351c0), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02669124, 0x026351c0))},
        };
    }

    bool AimBotPatch::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AimBotPatch)

    void AimBotWrapper::start() {
		AimBotUpdate *aimBotUpdateModule = silverlightInstance->m_moduleStates.getModule<AimBotUpdate>();
		AimBotPatch *aimBotPatchModule = silverlightInstance->m_moduleStates.getModule<AimBotPatch>();

		aimBotUpdateModule->m_enabled = true;
		aimBotPatchModule->enablePatch();
    }

    void AimBotWrapper::stop() {
		AimBotUpdate *aimBotUpdateModule = silverlightInstance->m_moduleStates.getModule<AimBotUpdate>();
		AimBotPatch *aimBotPatchModule = silverlightInstance->m_moduleStates.getModule<AimBotPatch>();

		aimBotUpdateModule->m_enabled = false;
		aimBotPatchModule->disablePatch();
    }

    void AimBotWrapper::update(float deltaTime) {
    }

    bool AimBotWrapper::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AimBotWrapper)
}
