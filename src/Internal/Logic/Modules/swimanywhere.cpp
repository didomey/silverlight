//
// Created by tv on 15.11.23.
//

#include "swimanywhere.h"
#include<Internal/silverlight.h>

void SwimAnywhere::start() {

}

void SwimAnywhere::stop() {
    g_playerMgr->m_swimSpeed = 1;
}

void SwimAnywhere::update(float deltaTime) {

    if (g_playerMgr == nullptr)
        return;
    g_playerMgr->m_swimSpeed = 128;
}

bool SwimAnywhere::isCheatModule() {
    return true;
}

REGISTERVCLASS(SwimAnywhere)
