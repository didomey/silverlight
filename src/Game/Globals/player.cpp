#include "player.h"

float &getHumanFov() {
    return *(float *) HUMAN_FOV;
}

float &getSquidFov() {
    return *(float *) SQUID_FOV;
}
