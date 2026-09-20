#pragma once

#include "Game/Macros.h"

namespace Game {
namespace CameraAccessor {
struct CameraAccessor {
  std::array<char, 0x58> unk1;
  uint32_t cameraControlState;
};

ENSURE_OFFSET(CameraAccessor, cameraControlState, 0x58);

GVARBIND(sInstance, 101dcdb4, CameraAccessor *)
} // namespace CameraAccessor
} // namespace Game
