#pragma once

#include "Game/Macros.h"

namespace Game {
	namespace PlayerMotion {
		#pragma pack(push, 1)
		struct PlayerMotionUnk1 {
			std::array<char, 0x760> unk1;
			uint32_t* playerInkAction;
		};

		ENSURE_OFFSET(PlayerMotionUnk1, playerInkAction, 0x760);

		struct PlayerMotion {
			Game::PlayerMotion::PlayerMotionUnk1* unk1;
			
			std::array<char, 0x30> unk2;
			uint32_t* playerAnimCtrlSet;
		};
		#pragma pack(pop)

		ENSURE_OFFSET(PlayerMotion, unk1, 0x0);

		FUNCBIND(changeBlend, 026be450, int32_t(*)(Game::PlayerMotion::PlayerMotion* _this, int32_t* animID, int32_t param_2, int32_t param_3))
		FUNCBIND(startEventAnim, 026bfbc8, int32_t(*)(Game::PlayerMotion::PlayerMotion* _this, int32_t *animID, float param_2, float param_3))
		FUNCBIND(FUN_026c7884, 026c7884, int32_t(*)(Game::PlayerMotion::PlayerMotion* _this, int32_t *animID))
	}
}
