#pragma once

#include "Game/Macros.h"
#include <glm/vec3.hpp>
#include "Matrix34.h"

namespace sead {
	namespace LookAtCamera {
		#pragma pack(push, 1)
		struct LookAtCamera {
		};
		#pragma pack(pop)

		FUNCBIND(doUpdateMatrix, 028e6d2c, void(*)(LookAtCamera* _this, sead::Matrix34* res))
	}
}
