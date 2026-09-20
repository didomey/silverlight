#pragma once

#include "Game/Macros.h"
#include <glm/vec3.hpp>

namespace Cmn {
	namespace PlayerWeapon {
		#pragma pack(push, 1)
		struct PlayerWeapon {
		};
		#pragma pack(pop)

		FUNCBIND(setChargeRate, 026d6700, void(*)(Cmn::PlayerWeapon::PlayerWeapon* _this, float amount))
	}
}
