#pragma once

#include "Game/Macros.h"

namespace Game {
	namespace CloneHandleBase {
		#pragma pack(push, 1)
		struct CloneHandleBase {
			std::array<char, 0x78> unk1;
			uint32_t playerCloneHandlesSize;
			std::array<char, 0x4> unk2;
			// make type later too lazy
			void** playerCloneHandles;
		};
		#pragma pack(pop)

		ENSURE_OFFSET(CloneHandleBase, playerCloneHandles, 0x78);
		ENSURE_OFFSET(Clone, playerCloneHandlesSize, 0x80);

		GVARBIND(sInstance, 101e22ac, CloneHandleBase*)
	}
}
