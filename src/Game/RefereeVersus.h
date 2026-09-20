#include "Game/Macros.h"

namespace Game {
	namespace RefereeVersus {
		#pragma pack(push, 1)
		struct RefereeVersus {
			std::array<char, 0x294> unk1;
			int intro;
			std::array<char, 0x10> unk2;
			int endGame;
		};

		ENSURE_OFFSET(RefereeVersus, intro, 0x294);
		ENSURE_OFFSET(RefereeVersus, endGame, 0x2A8);

		#pragma pack(pop)
	}
}
