#include "Game/Macros.h"

namespace Game {
namespace SaveUnk {
#pragma pack(push, 1)
struct SaveUnk {
  std::array<char, 0x512> unk;
};
#pragma pack(pop)

FUNCBIND(SaveUnkCtor, 021b18d8,
         Game::SaveUnk::SaveUnk *(*)(Game::SaveUnk::SaveUnk *_this))
FUNCBIND(getLastBitrate, 021b22fc, float (*)(Game::SaveUnk::SaveUnk *_this))
FUNCBIND(getRecentBitrateAverage, 021b2164,
         float (*)(Game::SaveUnk::SaveUnk *_this))
} // namespace SaveUnk
} // namespace Game
