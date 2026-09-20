#include<Internal/Logic/modules.h>
#include<nn/swkbd.h>

#include "cheatindicator.h"
#include "Shared/strop.h"

#include "Internal/silverlight.h"

#include "Shared/strop.h"

namespace Modules {
    REGISTERVCLASS(CheatIndicator)

    CheatIndicator::CheatIndicator() {
		this->m_enabled = true;
    }

    void CheatIndicator::start() {
    }

    void CheatIndicator::stop() {
    }

    void CheatIndicator::update(float deltaTime) {
    }

    void CheatIndicator::render(float deltaTime) {
        if (std::ranges::any_of(silverlightInstance->m_moduleStates.m_updateModules, [](auto &module) -> bool {
            return (module->m_enabled && module->isCheatModule());
        }) || std::ranges::any_of(silverlightInstance->m_moduleStates.m_patchModules, [](auto &module) -> bool {
            return (module->m_enabled && module->isCheatModule());
        })) {
            this->cheatsEnabled = true;
            silverlightInstance->m_renderer.setTextCursor({-75, 350});
            silverlightInstance->m_renderer.drawText("[CHEATS ENABLED]", {1, 0.0, 0.0, 1});
            return;
        }
        this->cheatsEnabled = false;
    }

    bool CheatIndicator::isCheatModule() {
        return false;
    }
}
