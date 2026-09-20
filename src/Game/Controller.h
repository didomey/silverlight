//
// Created by tv on 03.11.23.
//

#pragma once

#include<cstdint>
#include<optional>
#include <glm/vec3.hpp>
#include "Macros.h"
#include<array>

namespace Controller {
	#pragma pack(push, 1)
	struct Controller {
		std::array<char, 0x154> unk1;
		uint32_t showPauseScreenFrame;
		int32_t controlState;
	};

	ENSURE_OFFSET(Controller, controlState, 0x158);
	#pragma pack(pop)

	GVARBIND(sInstance, 101e6474, Controller *)
}
