#include"squidsurge.h"
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
#include <math.h>

namespace Modules {
    void SquidSurge::start() {
		this->phase = SquidSurgePhase::Inactive;
    }

    void SquidSurge::stop() {
    }

	void SquidSurge::stateInactive() {
		Game::Player::Player* player = Game::Player::localInstance;

		if (Game::Player::isAerial(player) || !Game::Player::isInSquid(player)) return;

		this->phase = SquidSurgePhase::InactiveReady;
	}

	void SquidSurge::stateInactiveReady() {
		Game::Player::Player* player = Game::Player::localInstance;

		if (!Game::Player::isAerial(player) || !Game::Player::isInSquid(player) || !Game::Player::isJumpOverZero(player)) return;

        VPADStatus status = {};
        VPADReadError err;
        VPADRead(VPAD_CHAN_0, &status, 1, &err);

		this->phase = SquidSurgePhase::Upward;
		this->dir = {status.leftStick.x, status.leftStick.y};
		this->initialActivePlayerPosition = player->position;
		this->position = player->position;
		this->verticalAccel = 3.0;
	}

	void SquidSurge::stateUpward() {
		Game::Player::Player* player = Game::Player::localInstance;

		if (this->verticalAccel <= 0.0) {
			this->phase = SquidSurgePhase::Downward;
			this->verticalAccel = 0.0;
		}

		this->verticalAccel -= 0.1;
		this->position.y += this->verticalAccel;
		player->position = this->position;
	}

	void SquidSurge::stateDownward() {
		Game::Player::Player* player = Game::Player::localInstance;

		if (!Game::Player::isAerial(player)) {
			this->phase = SquidSurgePhase::Inactive;
			return;
		}

		this->verticalAccel -= 0.2;
		this->position.y += this->verticalAccel;
		player->position = this->position;
	}

    void SquidSurge::update(float deltaTime) {
		Game::Player::Player* player = Game::Player::localInstance;

		switch (this->phase) {
			case SquidSurgePhase::Inactive:
				stateInactive();
				break;
			case SquidSurgePhase::InactiveReady:
				stateInactiveReady();
				break;
			case SquidSurgePhase::Upward:
				stateUpward();
				break;
			case SquidSurgePhase::Downward:
				stateDownward();
		}
    }

	void SquidSurge::render(float deltaTime) {
	}

    bool SquidSurge::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(SquidSurge)
}
