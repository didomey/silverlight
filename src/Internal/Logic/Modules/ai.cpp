//
// Created by tv on 04.11.23.
//
#include"ai.h"
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
#include "Game/Player.h"
#include "Game/StaticMem.h"
#include "Game/VictoryLift.h"

enum class AIState {
	Idle,
	TargetObjective,
	TargetPlayer,
	Retreat,
};

class AIStateMachine {
	AIState decideBestAttackState_TowerControl() {
		std::vector<Game::Player::Player*> enemies = Game::Utl::getAllEnemies();
		std::vector<Game::Player::Player*> teammates = Game::Utl::getAllTeammates();

		bool allEnemiesDead = true;

		for (const auto enemy : enemies) {
			if (enemy->isAlive) {
				allEnemiesDead = false;
				break;
			}
		}

		size_t aliveTeammateCnt = Game::Utl::getAliveTeammateCnt();
		size_t aliveEnemyCnt = Game::Utl::getAliveEnemyCnt();

		if (!Game::VictoryLift::isTowerMove() && aliveTeammateCnt >= aliveEnemyCnt) {
			return AIState::TargetObjective;
		}

		if (aliveEnemyCnt == 0) return AIState::TargetObjective;
		if (aliveTeammateCnt < aliveEnemyCnt) return AIState::Retreat;

		return AIState::TargetPlayer;
	}

	AIState decideBestAttackState() {
		switch (g_staticMem->m_mode) {
			// TC
			case 3:
				this->state = decideBestAttackState_TowerControl();
				break;
			default:
				break;
		};
	}

public:
	AIState state = AIState::Idle;

	AIStateMachine() {}

	void update() {
		if (!Game::Player::localInstance) return;
		if (!g_staticMem) return;
		if (!Game::Player::isInMatchIntro(Game::Player::localInstance)) {
			this->state = this->decideBestAttackState();
		}

		switch (this->state) {
			case AIState::Idle:
				this->state = this->stateIdle();
				break;
			case AIState::TargetObjective:
				this->state = this->stateTargetObjective();
				break;
			case AIState::TargetPlayer:
				this->state = this->stateTargetPlayer();
		};
	}

	AIState stateIdle() {
		return AIState::Idle;
	}

	AIState stateTargetObjective() {
		return AIState::TargetObjective;
	}

	AIState stateTargetPlayer() {
		return AIState::TargetPlayer;
	}
};

namespace Modules {

    void AIUpdate::start() {
    }

    void AIUpdate::stop() {
    }

    void AIUpdate::update(float deltaTime) {
    }

	void AIUpdate::render(float deltaTime) {
	}

    bool AIUpdate::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AIUpdate)
}
