#pragma once

#include "Game/Macros.h"

namespace Game {
	namespace Clone {
		#pragma pack(push, 1)
		struct Clone {
			std::array<char, 0x44> unk1;
			bool isOfflineScene;

			std::array<char, 0x13> unk2;
			uint32_t cloneId;
		};
		#pragma pack(pop)

		ENSURE_OFFSET(Clone, isOfflineScene, 0x44);
		ENSURE_OFFSET(Clone, cloneId, 0x58);
	}
}
