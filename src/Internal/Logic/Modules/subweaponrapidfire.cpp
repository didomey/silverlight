//
// Created by tv on 17.11.23.
//

#include "subweaponrapidfire.h"
#include<cstdint>
#include "Shared/Cafe/vpad.h"
#include<Game/MainMgr.h>
#include <vpad/input.h>

void SubWeaponRapidfire::start() {

}

void SubWeaponRapidfire::stop() {

}

void SubWeaponRapidfire::update(float deltaTime) {
    if (g_playerMgr == nullptr)
        return;

    VPADStatus status = {};
    VPADReadError err;

    VPADRead(VPAD_CHAN_0, &status, 1, &err);

    auto *inputs = (Inputs *) &status.hold;

    if (!inputs->ButtonR)
        return;

    g_playerMgr->m_hexF8Unk = 0x0;
    g_playerMgr->m_hexC8Unk = 0x4;
    g_playerMgr->m_HexE0Unk = 0x01000000;
    g_playerMgr->m_HexECUnk = 0x0;

    g_playerMgr->m_hex1D4Unk = 0x0;
    g_playerMgr->m_hex1E4Unk = 0x0;
    g_playerMgr->m_hex1ECUnk = 0x0;
    g_playerMgr->m_hex1F0Unk = 0x0;
    g_playerMgr->m_Hex4A0Unk = 0x0;
    g_playerMgr->m_Hex4A4Unk = 0x0;
    g_playerMgr->m_Hex4ACUnk = 0x0;
}

bool SubWeaponRapidfire::isCheatModule() {
    return true;
}

REGISTERVCLASS(SubWeaponRapidfire)
