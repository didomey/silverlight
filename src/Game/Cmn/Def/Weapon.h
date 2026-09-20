#pragma once

#include "Game/Macros.h"

namespace Cmn {
namespace Def {
struct Weapon {
  int32_t fullWeaponId;
  int32_t weaponId;
  int32_t subWeaponId;
  int32_t specialWeaponId;
  int32_t unk;
};

ENSURE_OFFSET(Weapon, fullWeaponId, 0x0);
ENSURE_OFFSET(Weapon, weaponId, 0x4);
ENSURE_OFFSET(Weapon, subWeaponId, 0x8);
ENSURE_OFFSET(Weapon, specialWeaponId, 0xc);
ENSURE_OFFSET(Weapon, unk, 0x10);
} // namespace Def
} // namespace Cmn
