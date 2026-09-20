#pragma once

#include "Game/Macros.h"
#include <glm/vec3.hpp>

namespace Game {
	namespace PaintCloneEvent {
		#pragma pack(push, 1)
		struct PaintCloneEvent {
			std::array<char, 0x24> unk1;
			uint8_t eventId;
		};
		#pragma pack(pop)

		ENSURE_OFFSET(PaintCloneEvent, eventId, 0x24);
	}
}
