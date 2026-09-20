#pragma once

#include "Game/Macros.h"
#include <glm/vec3.hpp>
#include "PlayerCloneObj.h"

namespace Game {
	namespace PaintCloneHandle {
		#pragma pack(push, 1)
		struct PaintCloneHandle {
			std::array<char, 0x14> unk1;
			Game::PlayerCloneObj::PlayerCloneObj* cloneEvent;
		};
		#pragma pack(pop)

		ENSURE_OFFSET(PaintCloneHandle, cloneEvent, 0x14);

		FUNCBIND(receive, 0266bf74, void(*)(Game::PaintCloneHandle::PaintCloneHandle* _this, Game::Player::Player* player, int32_t param_2))
	}
}
