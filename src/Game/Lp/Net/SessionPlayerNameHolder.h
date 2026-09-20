#pragma once

#include "Game/Macros.h"
#include "Game/UniqueID.h"

namespace Lp {
namespace Net {
namespace SessionPlayerNameHolder {
struct SessionPlayerNameHolder {};

FUNCBIND(
    findPlayerName, 027b1d70,
    short *(*)(Lp::Net::SessionPlayerNameHolder::SessionPlayerNameHolder *_this,
               uint32_t *pid))

GVARBIND(sInstance, 101e5680,
         Lp::Net::SessionPlayerNameHolder::SessionPlayerNameHolder *)
} // namespace SessionPlayerNameHolder
} // namespace Net
} // namespace Lp
