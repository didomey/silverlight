#include "Shared/Core/Logging.h"
#include "Shared/Cafe/vpad.h"

#include "fovchanger.h"
#include "Game/Globals/player.h"

namespace Modules {
    void fovChanger(float deltaTime) {
        VPADStatus status = {};
        VPADReadError err;

        VPADRead(VPAD_CHAN_0, &status, 1, &err);

        Inputs *inputs = (Inputs *) &status.hold;

        float *humanFOVPtr = (float *) 0x100e9ab8;
        float *squidFOVPtr = (float *) 0x100e9a28;

        if (inputs->StickREmulationLeft) {
            // Human
            getHumanFov() = getHumanFov() + deltaTime * 100;
            // Squid
            getSquidFov() = getSquidFov() + deltaTime * 100;
            CAFEINFO("Fov changed to: " + std::to_string(*(float *) 0x100e9ab8));
        } else if (inputs->StickREmulationRight) {
            // Human
            getHumanFov() = getHumanFov() - deltaTime * 100;
            // Squid
            getSquidFov() = getSquidFov() - deltaTime * 100;
            CAFEINFO("Fov changed to: " + std::to_string(*(float *) 0x100e9ab8));
        }
    }
}
