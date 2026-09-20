//
// Created by tv on 04.11.23.
//
#include"specialalwayscharged.h"
#include "Game/Globals/weapon.h"

namespace Modules {
    void SpecialAlwaysCharged::start() {
		SPECIAL_GAUGE = 0xBF400000;
    }

    void SpecialAlwaysCharged::stop() {
		SPECIAL_GAUGE = 0x43300000;
    }

    void SpecialAlwaysCharged::update(float deltaTime) {
	}

    bool SpecialAlwaysCharged::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(SpecialAlwaysCharged)
}
