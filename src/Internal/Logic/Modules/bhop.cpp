//
// Created by tv on 04.11.23.
//
#include"bhop.h"
#include "Shared/Core/Logging.h"
#include "Shared/Cafe/vpad.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<vpad/input.h>
#include<glm/mat3x3.hpp>
#include<Game/Assembler/ppcAssembler.h>

#include "Game/Globals/Unk.h"
#include "Game/Globals/player.h"

namespace Modules {

    void BHop::start() {
        *JUMP_HEIGHT = 0.8;
    }

    void BHop::stop() {
        *UNK105EC2E4 = 3.55;
        *UNK105EBFF0 = 0.4;
        *JUMP_HEIGHT = 1.15;
    }

    void BHop::update(float deltaTime) {

        if (g_playerMgr == nullptr)
            return;

        if (g_playerMgr->m_playerBehindCamera == nullptr)
            return;

        VPADStatus status = {};
        VPADReadError err;

        VPADRead(VPAD_CHAN_0, &status, 1, &err);

        auto *inputs = (Inputs *) &status.hold;

        if (inputs->ButtonX) {
            g_playerMgr->m_HexC4Unk = 0xFFFF;
            g_playerMgr->m_Hex348Unk = 6;
            g_playerMgr->m_Hex898Unk = 0x0;
            g_playerMgr->m_Hex89CUnk = 0x0;
            g_playerMgr->m_Hex8A0Unk = 0x0;
            if (g_playerMgr->m_Hex5CCUnk != 0x0)
                g_playerMgr->m_Hex4C0Unk = 64;

            *UNK105EC2E4 = 3.55;
            *UNK105EBFF0 = 0.4;
        } else {
            *UNK105EC2E4 = 1.15;
            *UNK105EBFF0 = 0.1;
        }

        if (!inputs->ButtonX) {
            return;
        }

        glm::vec3 moveDirRelative = {
                status.leftStick.y,
                0.0f,
                -status.leftStick.x
        };

        glm::vec3 forwardDir = g_playerMgr->m_playerBehindCamera->m_playerMoveRotation;
        glm::vec3 upDir = {0.0f, 1.0f, 0.0f};
        glm::vec3 rightDir = glm::cross(upDir, forwardDir);

        glm::mat3x3 rotationMatrix = {
                forwardDir,
                upDir,
                rightDir
        };

        glm::vec3 moveDirection = rotationMatrix * moveDirRelative;

        g_playerMgr->m_player1Position.x += moveDirection.x * deltaTime * 150;
        g_playerMgr->m_player1Position.z += moveDirection.z * deltaTime * 150;
    }

    bool BHop::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(BHop)
}
