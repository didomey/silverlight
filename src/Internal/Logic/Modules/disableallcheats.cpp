#include "Internal/silverlight.h"

namespace Modules {
    void disableAllCheats() {

        for (const auto &module: silverlightInstance->m_moduleStates.m_updateModules) {
            if (module->isCheatModule()) {
                module->disable();
            }
        }

        for (const auto &module: silverlightInstance->m_moduleStates.m_patchModules) {
            if (module->isCheatModule()) {
                module->disablePatch();
            }
        }

    }
}
