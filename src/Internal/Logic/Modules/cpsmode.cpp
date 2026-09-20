//
// Created by tv on 04.11.23.
//
#include"cpsmode.h"
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
#include "Internal/silverlight.h"

namespace Modules {

    void CPSMode::start() {
    }

    void CPSMode::stop() {
    }

    void CPSMode::update(float deltaTime) {
		Game::Player::Player* player = Game::Player::localInstance;

		if (!player) return;
		if (!player->isShooting) return;
		if (!player->playerDamage) return;

		if (player->shotBulletsNum > 2 && player->playerDamage->damageTaken <= 0.95) {
			player->playerDamage->damageTaken += 0.05;
		}
    }

	void CPSMode::render(float deltaTime) {
	}

    bool CPSMode::isCheatModule() {
        return true;
    }

	std::string CPSMode::helpText() {
		return "Shoot more than once without letting go of the shoot trigger and you get damaged!";
	}

    REGISTERVCLASS(CPSMode)
}
