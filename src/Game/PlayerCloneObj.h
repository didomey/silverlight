#pragma once

#include "Game/Macros.h"

namespace Game {
	namespace PlayerCloneObj {
		#pragma pack(push, 1)
		struct PlayerCloneObj {
		};
		#pragma pack(pop)

		FUNCBIND(popRecvEvent, 02ce3224, void(*)(Game::PlayerCloneObj::PlayerCloneObj* _this, int32_t cloneEvent))
	}
}
