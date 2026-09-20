#pragma once

#include "Game/Macros.h"

namespace sead {
namespace Random {
struct Random {};

FUNCBIND(getU32, 028fc0dc, uint32_t (*)(sead::Random::Random *_this))
} // namespace Random
} // namespace sead
