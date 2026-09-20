//
// Created by tv on 04.11.23.
//
#include"bubblyhair.h"
#include <Game/Globals/Unk.h>
#include "Shared/Cafe/vpad.h"
#include "Game/Unk2.h"
#include "Game/Globals/player.h"

namespace Modules {

    void BubblyHair::start() {
		UNK_BUBBLY_HAIR = 0.0;
    }

    void BubblyHair::stop() {
		UNK_BUBBLY_HAIR = 1.0;
    }

    void BubblyHair::update(float deltaTime) {
    }

    bool BubblyHair::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(BubblyHair)
}
