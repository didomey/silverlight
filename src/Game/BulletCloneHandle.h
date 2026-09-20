#pragma once

#include "Game/Macros.h"
#include <glm/vec3.hpp>
#include "PlayerCloneObj.h"

namespace Game {
	namespace BulletCloneHandle {
		#pragma pack(push, 1)
		struct BulletCloneHandle {
			std::array<char, 0x182c> unk1;
			Game::PlayerCloneObj::PlayerCloneObj* cloneEvent;
		};
		#pragma pack(pop)

		ENSURE_OFFSET(BulletCloneHandle, cloneEvent, 0x182c);

		FUNCBIND(receive, 0266c6f4, void(*)(Game::BulletCloneHandle::BulletCloneHandle* _this, Game::Player::Player* player, int32_t param_2))
	}
}
