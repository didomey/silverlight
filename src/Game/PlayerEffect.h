#include "Game/Macros.h"
#include <glm/vec3.hpp>

namespace Game {
	namespace PlayerEffect {
		#pragma pack(push, 1)
		struct PlayerEffect {
		};
		#pragma pack(pop)

		FUNCBIND(emitAndPlay_Vanish, 02655c70, void(*)(Game::PlayerEffect::PlayerEffect* _this))
	}
}
