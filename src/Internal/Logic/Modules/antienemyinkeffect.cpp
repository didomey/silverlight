//
// Created by tv on 04.11.23.
//
#include"antienemyinkeffect.h"
#include <Game/Globals/Unk.h>
#include "Shared/Cafe/vpad.h"
#include "Game/Unk2.h"
#include "Game/Globals/player.h"
#include "Game/MainMgr.h"

namespace Modules {

    void AntiEnemyInkEffect::start() {
    }

    void AntiEnemyInkEffect::stop() {
    }

    void AntiEnemyInkEffect::update(float deltaTime) {
        g_playerMgr->m_Hex8A0Unk = 0x3E000000;
        g_playerMgr->m_Hex8A4Unk = 0x3E000000;
    }

    bool AntiEnemyInkEffect::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AntiEnemyInkEffect)
}
