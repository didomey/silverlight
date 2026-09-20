#pragma once

#include "Game/Macros.h"

namespace Game {
	namespace PlayerInkAction {
		struct PlayerInkAction {
			std::array<char, 0x1c> unk2;
			float inkTank;

			std::array<char, 0x50> unk5;
			uint16_t chargeFrm;

			std::array<char, 0x4cc> unk3;
			uint32_t chargeState;
		};

		ENSURE_OFFSET(PlayerInkAction, inkTank, 0x1c);
		ENSURE_OFFSET(PlayerInkAction, chargeFrm, 0x70);
		ENSURE_OFFSET(PlayerInkAction, chargeState, 0x540);

		FUNCBIND(requestBrushAnim, 026a37b0, int32_t(*)(uint32_t* _this, uint32_t brushAnim))

		FUNCBIND(setGuideValid, 026a6278, int32_t(*)(uint32_t* _this))
		FUNCBIND(setGuideInvalid, 026a6288, int32_t(*)(uint32_t* _this))

		FUNCBIND(calcShot, 0269c72c, int32_t(*)(uint32_t* _this, int isFirstFrame))

		FUNCBIND(getBombThrowSpanFrm, 0269f53c, int32_t(*)(uint32_t* _this, int32_t unk1))
	}
}
