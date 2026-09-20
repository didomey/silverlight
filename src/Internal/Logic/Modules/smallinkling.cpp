//
// Created by tv on 04.11.23.
//
#include"smallinkling.h"
#include "Game/Globals/player.h"

namespace Modules {

    void SmallInkling::start() {
		PLAYER_SIZE = 0.5;
    }

    void SmallInkling::stop() {
		PLAYER_SIZE = 1.0;
    }

    void SmallInkling::update(float deltaTime) {
	}

    bool SmallInkling::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(SmallInkling)
}
