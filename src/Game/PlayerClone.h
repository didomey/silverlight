#include "Game/Macros.h"
#include <glm/vec3.hpp>

namespace Game {
	namespace PlayerCloneHandle {
		#pragma pack(push, 1)

		struct PlayerCloneObj {
			std::array<char, 0x1c> unk1;
			uint8_t eventId;
		};

		struct PlayerCloneHandle {
		};
		
		#pragma pack(pop)

		FUNCBIND(unpackStateEvent, 0266aef0, int32_t(*)(Game::Player::Player* player, Game::PlayerCloneHandle::PlayerCloneObj* event, uint32_t* cloneHandleIdx))
		FUNCBIND(receive, 0266ecf8, void(*)(Game::PlayerCloneHandle::PlayerCloneHandle* _this, Game::Player::Player* player, int32_t cloneHandleIdx))
	}
}
