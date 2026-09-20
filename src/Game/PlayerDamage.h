#pragma once

#include "Game/Macros.h"

namespace Game {
namespace PlayerDamage {
#pragma pack(push, 1)
struct PlayerDamage {
  std::array<char, 0x28> unk1;
  float damageRt;
  std::array<char, 0xc> unk2;
  uint32_t *damageReason;
  uint32_t *damageReason2;

  std::array<char, 0x14> unk3;
  float damageUnk1;
  float damageTaken;
  float damageUnk3;
};

#pragma pack(pop)

ENSURE_OFFSET(PlayerDamage, damageRt, 0x28);
ENSURE_OFFSET(PlayerDamage, damageReason, 0x38);
ENSURE_OFFSET(PlayerDamage, damageReason2, 0x3c);
ENSURE_OFFSET(PlayerDamage, damageUnk1, 0x54);
ENSURE_OFFSET(PlayerDamage, damageTaken, 0x58);
ENSURE_OFFSET(PlayerDamage, damageUnk3, 0x5c);

FUNCBIND(setDamageRt, 02681328,
         void (*)(Game::PlayerDamage::PlayerDamage *_this, float damageRt))
FUNCBIND(procNetDivDamageFrame, 02680dd4,
         void (*)(Game::PlayerDamage::PlayerDamage *_this))
FUNCBIND(setDamage, 02681560,
         void (*)(Game::PlayerDamage::PlayerDamage *_this, double damage))
} // namespace PlayerDamage
} // namespace Game
