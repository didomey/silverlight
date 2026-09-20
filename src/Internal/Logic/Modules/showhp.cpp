#include"showhp.h"
#include "Internal/silverlight.h"
#include "Game/MainMgr.h"

namespace Modules {
    ShowHP::ShowHP() {
        this->m_enabled = true;
    }

    void ShowHP::start() {
    }

    void ShowHP::stop() {
    }

    void ShowHP::update(float deltaTime) {
    }

    void ShowHP::render(float deltaTime) {
        if (0x20000000 < ((uint32_t) g_playerMgr->m_unk3) &&
            ((uint32_t) g_playerMgr->m_unk3) < 0x30000000) {


            float damageTaken = g_playerMgr->m_unk3->m_damageTaken;
            float health = 100.0 - (damageTaken * 100.0);

            glm::vec4 color;

            if (health >= 80.0) {
                color = {0, 255, 0, 1};
            } else if (health >= 60.0) {
                color = {255, 165, 0, 1};
            } else {
                color = {255, 0, 0, 1};
            }

            std::string dispText = "HP: " + to_string_with_precision(health, 2);

            silverlightInstance->m_renderer.setTextCursor({-(dispText.length() * 9.600006 / 2), -325});
            silverlightInstance->m_renderer.drawText(dispText, color);
        }
    }

    bool ShowHP::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(ShowHP)
}
