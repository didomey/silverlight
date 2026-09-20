#pragma once

#include "Game/Macros.h"
#include <cstdint>
#include <cstddef>

namespace Cmn {
	namespace Def {
		struct Gear {
			int32_t gearId;
			int32_t filledAbilitySlotsNum;
			int32_t unlockedAbilitySlotsNum;
			int32_t leftSubAbilityId;
			int32_t middleSubAbilityId;
			int32_t rightSubAbilityId;
			int32_t unk;
		};

		ENSURE_OFFSET(Gear, gearId, 0x0);
		ENSURE_OFFSET(Gear, filledAbilitySlotsNum, 0x4);
		ENSURE_OFFSET(Gear, unlockedAbilitySlotsNum, 0x8);
		ENSURE_OFFSET(Gear, leftSubAbilityId, 0xc);
		ENSURE_OFFSET(Gear, middleSubAbilityId, 0x10);
		ENSURE_OFFSET(Gear, rightSubAbilityId, 0x14);
		ENSURE_OFFSET(Gear, unk, 0x18);
	}
}
