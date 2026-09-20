#include"squidroll.h"
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
#include <cmath>

namespace Modules {
    void SquidRoll::start() {
		this->state = SquidRollState::Inactive;
    }

    void SquidRoll::stop() {
    }

	void SquidRoll::stateInactive() {
		Game::Player::Player* player = Game::Player::localInstance;

		if (Game::Player::isAerial(player) || !Game::Player::isInSquid(player)) return;

		this->bufIdx = 0;

		this->state = SquidRollState::StickInputCheck;
	}

	void SquidRoll::stateStickInputCheck() {
		Game::Player::Player* player = Game::Player::localInstance;

		if (player->jumpState != 0) {
			this->state = SquidRollState::Inactive;
			return;
		}

        VPADStatus status = {};
        VPADReadError err;
        VPADRead(VPAD_CHAN_0, &status, 1, &err);

		this->stickPos = {status.leftStick.x, status.leftStick.y};

		bool stickTurnedEnough = false;

		std::vector<glm::vec2> validatedStickPositions = {};

		for (uint32_t i = 0; i < bufIdx; i++) {
			glm::vec2 bufStickPos = stickPosBuf[i];

			if (bufStickPos.x == 0.0 || bufStickPos.y == 0.0) continue;

			float stickPosDotProduct = glm::dot(stickPos, bufStickPos);

			float stickPosMag = glm::length(this->stickPos);
			float bufStickPosMag = glm::length(bufStickPos);

			float stickPosAngleDiff = acos(stickPosDotProduct / (stickPosMag * bufStickPosMag));

			if (stickPosAngleDiff >= MIN_STICK_DIST) {
				validatedStickPositions.push_back(bufStickPos);
				stickTurnedEnough = true;
			}
		}

		if (!validatedStickPositions.empty()) {
			glm::vec2 bufStickPos = validatedStickPositions[validatedStickPositions.size() - 1];
			this->stickPos = bufStickPos;
		}

		this->stickPosBuf[this->bufIdx] = {status.leftStick.x, status.leftStick.y};
		this->bufIdx++;

		uint32_t stickPosBufLen = sizeof(stickPosBuf) / sizeof(glm::vec2);

		if (this->bufIdx >= stickPosBufLen) {
			this->bufIdx = 0;
		}

		if (!stickTurnedEnough) return;

		this->remainingPossibleJumpFrm = JUMP_FRM_WINDOW;

		this->state = SquidRollState::JumpInputCheck;
	}

	void SquidRoll::stateJumpInputCheck() {
		Game::Player::Player* player = Game::Player::localInstance;

		if (this->remainingPossibleJumpFrm < 1) {
			this->state = SquidRollState::Inactive;

			return;
		}

        VPADStatus status = {};
        VPADReadError err;
        VPADRead(VPAD_CHAN_0, &status, 1, &err);

		if (status.leftStick.x != 0.0 && status.leftStick.y != 0.0) {
			// Player may move the left stick more before they jump
			this->stickPos = {status.leftStick.x, status.leftStick.y};
		}

		this->remainingPossibleJumpFrm--;

		if (!Game::Player::isJumpOverZero(player)) return;

		DisableJumpEffectHook *disableJumpEffectModule = silverlightInstance->m_moduleStates.getModule<DisableJumpEffectHook>();
		disableJumpEffectModule->enablePatch();

		this->initialActivePlayerPosition = player->position;
		this->position = player->position;
		this->verticalAccel = INITIAL_ACCEL;

		this->state = SquidRollState::Upward;
	}

	void SquidRoll::stateMoveHorizontal() {
		Game::Player::Player* player = Game::Player::localInstance;

		player->kingSquid->jumpAnimFrm = 100;

		player->kingSquid->state = 2;

		//Cmn::PlayerWeaponKingSquid::handlePlayerKrakenJumpAnim(player->kingSquid);

		gsys::Model::setVisible(player->kingSquid->model, 0x291cf9b0, 0);
		Cmn::PlayerWeaponKingSquid::attack(player->kingSquid);
		gsys::Model::requestDraw(player->kingSquid->model);
		//Cmn::PlayerWeaponKingSquid::updateAnimState(player->kingSquid);
		
		if (this->stickPos.x == 0.0 || this->stickPos.y == 0.0) return;

		glm::vec2 normalizedStickPos = {};

		float stickPosVecMagnitude = sqrt(pow(stickPos.x, 2) + pow(stickPos.y, 2));

		if (stickPosVecMagnitude == 0.0) return;

		normalizedStickPos.x = stickPos.x / stickPosVecMagnitude;
		normalizedStickPos.y = stickPos.y / stickPosVecMagnitude;

		glm::vec3 playerPitchVec = player->playerBehindCamera->pitch;

		double playerPitchAngle = atan2(playerPitchVec.y, sqrt(pow(playerPitchVec.x, 2) + pow(playerPitchVec.z, 2)));
    	double playerPitchAngleDeg = playerPitchAngle * (180.0 / M_PI);
    	double playerFacingAngle = 90.0 - playerPitchAngleDeg;

		CAFEINFO("Normalized: " + glm::to_string(normalizedStickPos));
		CAFEINFO("Player Angle: " + std::to_string(playerFacingAngle));

		this->position.z += normalizedStickPos.y * 1.5;
		this->position.x += normalizedStickPos.x * 1.5;
	}

	void SquidRoll::stateUpward() {
		Game::Player::Player* player = Game::Player::localInstance;

		if (this->verticalAccel <= 0.0) {
			this->verticalAccel = 0.0;

			this->state = SquidRollState::Downward;
		}

		player->armor = 2;

		this->verticalAccel -= UPWARD_ACCEL;
		this->position.y += this->verticalAccel;
		player->position = this->position;
	}

	void SquidRoll::stateDownward() {
		Game::Player::Player* player = Game::Player::localInstance;

		if (player->jumpState == 0) {
			this->state = SquidRollState::Inactive;

			DisableJumpEffectHook *disableJumpEffectModule = silverlightInstance->m_moduleStates.getModule<DisableJumpEffectHook>();
			disableJumpEffectModule->disablePatch();

			this->remainingInvincibilityFrm = EXTRA_ARMOR_FRM;

			return;
		}

		player->armor = 2;

		if (this->verticalAccel > MAX_DOWNWARD_ACCEL) {
			this->verticalAccel -= DOWNWARD_ACCEL;
		}

		this->position.y += this->verticalAccel;
		player->position = this->position;
	}

	void SquidRoll::stateArmorCheck() {
		Game::Player::Player* player = Game::Player::localInstance;

		if (this->remainingInvincibilityFrm > 0) {
			player->armor = 2;
			this->remainingInvincibilityFrm--;
		} else {
			player->armor = 1;
		}
	}

    void SquidRoll::update(float deltaTime) {
		Game::Player::Player* player = Game::Player::localInstance;

		if (!player) {
			this->state = SquidRollState::Inactive;
			return;
		}

		if (player->deathFrm > 0) {
			this->state = SquidRollState::Inactive;
			return;
		}

		switch (this->state) {
			case SquidRollState::Inactive:
				this->stateArmorCheck();
				this->stateInactive();
				break;
			case SquidRollState::StickInputCheck:
				this->stateArmorCheck();
				this->stateStickInputCheck();
				break;
			case SquidRollState::JumpInputCheck:
				this->stateArmorCheck();
				this->stateJumpInputCheck();
				break;
			case SquidRollState::Upward:
				this->stateMoveHorizontal();
				this->stateUpward();
				break;
			case SquidRollState::Downward:
				this->stateMoveHorizontal();
				this->stateDownward();
		}
    }

	void SquidRoll::render(float deltaTime) {
	}

    bool SquidRoll::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(SquidRoll)

	DisableJumpEffectHook::DisableJumpEffectHook() {
		this->patch = {
			{0x026b93ac, PatchElement("blr", "mflr r0")}
		};
	}

	bool DisableJumpEffectHook::isCheatModule() {
		return false;
	}

    REGISTERVCLASS(DisableJumpEffectHook)
}
