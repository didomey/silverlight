#include <cstdint>
#include "Game/Macros.h"

inline const uint32_t HUMAN_FOV = 0x100e9ab8;
inline const uint32_t SQUID_FOV = 0x100e9a28;

static float* JUMP_HEIGHT = (float*)0x100e92e4;

GVARBIND(PLAYER_CTRL_VOICE_BANK, 100e96b8, char*);

GVARBIND(PLAYER_SIZE, 100ec2b0, float);

GVARBIND(UNK_BUBBLY_HAIR, 100ea734, float);


float &getHumanFov();

float &getSquidFov();
