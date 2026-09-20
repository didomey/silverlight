//
// Created by tv on 04.11.23.
//
#include"specialalwaysactive.h"
#include <Game/Globals/Unk.h>
#include "Shared/Cafe/vpad.h"
#include "Game/Unk2.h"
#include "Game/MainMgr.h"


namespace Modules {

    void SpecialAlwaysActive::start() {
    }

    void SpecialAlwaysActive::stop() {
    }

    void SpecialAlwaysActive::update(float deltaTime) {
		getMainMgr()->m_unk8 = 0x0FFFFFFF;
		getMainMgr()->m_unk7 = 0xF;
    }

    bool SpecialAlwaysActive::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(SpecialAlwaysActive)
}
