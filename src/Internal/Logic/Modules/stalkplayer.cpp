//
// Created by tv on 04.11.23.
//
#include"stalkplayer.h"
#include<Game/MainMgr.h>
#include "Shared/Cafe/vpad.h"
#include "Internal/silverlight.h"

namespace Modules {
    void StalkPlayer::start() {
        this->selectedPlayer = 2;
        m_lastPlayerPosition = g_playerMgr->m_player1Position;
    }

    void StalkPlayer::stop() {
        g_playerMgr->m_player1Position = m_lastPlayerPosition;
    }

    void StalkPlayer::update(float deltaTime) {
        if (g_playerMgr == nullptr)
            return;

        static Inputs lastHeld = {};

        VPADStatus status = {};
        VPADReadError err;

        VPADRead(VPAD_CHAN_0, &status, 1, &err);

        Inputs *inputs = (Inputs *) &status.hold;

        if (inputs->StickLEmulationLeft && !lastHeld.StickLEmulationLeft) {
            this->selectedPlayer--;
        } else if (inputs->StickLEmulationRight && !lastHeld.StickLEmulationRight) {
            this->selectedPlayer++;
        }

        if (this->selectedPlayer > 8) {
            this->selectedPlayer--;
        } else if (this->selectedPlayer < 1) {
            this->selectedPlayer++;
        }

        glm::vec3 *selectedPos = (glm::vec3 *) (((char *) &g_playerMgr->m_player2Position + 0x1184 * selectedPlayer) -
                                                0x1184);

        g_playerMgr->m_player1Position.x = selectedPos->z;
        g_playerMgr->m_player1Position.y = selectedPos->x + 50.0;
        g_playerMgr->m_player1Position.z = selectedPos->y;

        lastHeld = *inputs;
    }

    void StalkPlayer::render(float deltaTime) {
        std::string text = "Player: " + std::to_string(this->selectedPlayer);
        if (!text.empty()) {
            silverlightInstance->m_renderer.setTextCursor({-(text.length() * 9.600006 / 2), 0});
            silverlightInstance->m_renderer.drawText(text);
        }
    }

    bool StalkPlayer::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(StalkPlayer)
}
