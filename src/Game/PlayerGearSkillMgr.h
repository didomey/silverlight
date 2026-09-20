#include "Game/Macros.h"
#include <glm/vec3.hpp>

namespace Game {
	namespace PlayerGearSkillMgr {
		#pragma pack(push, 1)
		struct PlayerGearSkillMgr {
			std::array<char, 0x70> unk1;
			uint32_t mainAbilityIds;
		};
		#pragma pack(pop)
	}
}
