//
// Created by tv on 04.11.23.
//
#include"disablespawnbarrier.h"
#include "Game/Globals/Unk.h"

namespace Modules {

    void DisableSpawnBarrier::start() {
    }

    void DisableSpawnBarrier::stop() {
		*UNK100D4F10 = 66;
    }

    void DisableSpawnBarrier::update(float deltaTime) {
		*UNK100D4F10 = 0;
	}

    bool DisableSpawnBarrier::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(DisableSpawnBarrier)
}
