#include <vpad/input.h>

#include "Shared/Cafe/vpad.h"
#include "Shared/Core/Logging.h"
#include "controller.h"
#include <Internal/silverlight.h>
#include <cstring>
#include<Shared/CemuBind.h>

#include "Modules/fovchanger.h"
#include<Game/Assembler/ppcAssembler.h>

#include "Internal/Logic/Modules/emote.h"

namespace Controller {
    void controllerCheck(float deltaTime) {
        static Inputs lastHeld = {};

        VPADStatus status = {};
        VPADReadError err;

        VPADRead(VPAD_CHAN_0, &status, 1, &err);

        Inputs *held = (Inputs *) &status.hold;

        // Modules that can be enabled and disabled

        if ((held->ButtonL && held->ButtonLeft) &&
            !(lastHeld.ButtonL && lastHeld.ButtonLeft)) {
            silverlightInstance->m_drawMenu ^= true;
        }

        // Other modules
        if (held->ButtonL) {
            Modules::fovChanger(deltaTime);
        }

		if (held->ButtonL && held->ButtonB && !lastHeld.ButtonB) {
			Modules::UpdateModule* emoteWrapperModule = silverlightInstance->m_moduleStates.getModule<Modules::EmoteWrapper>();

			if (emoteWrapperModule) {
				if (emoteWrapperModule->m_enabled) {
					emoteWrapperModule->disable();
				} else {
					emoteWrapperModule->enable();
				}
			}
		}

        if (silverlightInstance->m_drawMenu && silverlightInstance->m_menuControl) {
            if (held->ButtonDown && !lastHeld.ButtonDown) {
                silverlightInstance->m_menu->cursorDown();
            }

            if (held->ButtonUp && !lastHeld.ButtonUp) {
                silverlightInstance->m_menu->cursorUp();
            }

            if (held->ButtonRight && !lastHeld.ButtonRight) {
                silverlightInstance->m_menu->click();
            }
        }

        lastHeld = *held;
    }
} // namespace Controller
