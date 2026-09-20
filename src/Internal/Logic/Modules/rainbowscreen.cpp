#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include "rainbowscreen.h"

FUNCBIND(changeScreenColor, 02a0a278, void(*)(float, uint32_t))

GVARBIND(mainmgrsInst, 101E2814, uint32_t)

namespace Modules {

    void RainbowScreen::start() {
    }

    void RainbowScreen::stop() {
    }

    void RainbowScreen::update(float deltaTime) {
        static float val = 0;
        val += deltaTime * 60;
        while (val >= 360)
            val -= 360;
        if (ISINBOUNDS(mainmgrsInst)) {
            uint32_t val1 = *(uint32_t *) (mainmgrsInst + 0x25c);
            if (ISINBOUNDS(val1)) {
                uint32_t val2 = *(uint32_t *) (val1 + 8);

                if (ISINBOUNDS(val2)) {
                    uint32_t val3 = *(uint32_t *) (val2 + 0x2900);
                    if (ISINBOUNDS(val3)) {
                        changeScreenColor(val, val3);
                    }
                }
            }
        }
    }

    bool RainbowScreen::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(RainbowScreen)
}
