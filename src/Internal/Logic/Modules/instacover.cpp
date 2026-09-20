//
// Created by tv on 04.11.23.
//
#include"instacover.h"
#include <Game/Globals/Unk.h>

namespace Modules {

    void InstaCover::start() {
    }

    void InstaCover::stop() {
		*UNK100E92C0 = 0x40F00000;
		*UNK10032ED8 = 0x42200000;
		*UNK10034D10 = 0x42200000;
    }

    void InstaCover::update(float deltaTime) {
		*UNK100E92C0 = 0x4FF00000;
		*UNK10032ED8 = 0x49000000;
		*UNK10034D10 = 0x47200000;
    }

    bool InstaCover::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(InstaCover)
}
