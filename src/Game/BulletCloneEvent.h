#pragma once

#include "Game/Macros.h"
#include <glm/vec3.hpp>

namespace Game {
	namespace BulletCloneEvent {
		#pragma pack(push, 1)
		struct BulletCloneEvent {
			std::array<char, 0x19> unk1;
			uint8_t eventId;
		};
		#pragma pack(pop)

		ENSURE_OFFSET(BulletCloneEvent, eventId, 0x19);
	}
}
