#include "Game/Macros.h"

namespace Game {
	namespace PlayerTroubleUnk {
		#pragma pack(push, 1)

		struct PlayerTroubleUnkUnk {
			std::array<char, 0x2a> unk1;
			int playerIsDead;
		};

		ENSURE_OFFSET(PlayerTroubleUnkUnk, playerIsDead, 0x2a);
		
		struct PlayerTroubleUnk {
			std::array<char, 0x4ec> unk1;
			PlayerTroubleUnkUnk* m_unk1;
		};

		#pragma pack(pop)

		ENSURE_OFFSET(PlayerTroubleUnk, m_unk1, 0x4ec);

		GVARBIND(sInstance, 101e2270, PlayerTroubleUnk*)
	}
}
