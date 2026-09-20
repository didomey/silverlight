#pragma once

#include "Game/Macros.h"
#include "Game/UniqueID.h"

namespace enl {
	namespace PiaUtil {
		FUNCBIND(GetCurSessionHostPrincipalID, 02b3481c, int32_t(*)(void))

		FUNCBIND(GetStationPlayerName, 02b3285c, bool(*)(const char* playerInfo, enl::UniqueID* uuidPtr))
	}
}
