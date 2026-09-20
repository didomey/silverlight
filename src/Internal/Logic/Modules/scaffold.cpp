//
// Created by tv on 04.11.23.
//
#include"scaffold.h"
#include "Shared/Core/Logging.h"
#include "Shared/Cafe/vpad.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<vpad/input.h>
#include<glm/mat3x3.hpp>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    void Scaffold::start() {
    }

    void Scaffold::stop() {
    }

    void Scaffold::update(float deltaTime) {
        if (g_playerMgr == nullptr)
            return;

        g_playerMgr->m_Hex5A4Unk = 0;
        g_playerMgr->m_Hex5A8Unk = 0;
        g_playerMgr->m_Hex5ACUnk = 0;
        g_playerMgr->m_Hex5B0Unk = 0;
        g_playerMgr->m_Hex5B4Unk = 0;
        g_playerMgr->m_Hex5B8Unk = 0;
        g_playerMgr->m_Hex59CUnk = 0;
    }

    bool Scaffold::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(Scaffold)
}
