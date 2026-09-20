#pragma once

#include "Game/Macros.h"
#include <glm/vec3.hpp>

namespace Game {
	namespace PlayerBehindCamera {
	struct PlayerBehindCamera {
		std::array<char, 0x48> unk1;
		glm::vec3 upCamera;

		std::array<char, 0xc> unk4;
		glm::vec3 forwardCamera;

		std::array<char, 0x8c> unk2;
		glm::vec3 yaw;

		std::array<char, 0xb4> unk3;
		glm::vec3 pitch;
	};

	ENSURE_OFFSET(PlayerBehindCamera, upCamera, 0x48);
	ENSURE_OFFSET(PlayerBehindCamera, forwardCamera, 0x60);
	ENSURE_OFFSET(PlayerBehindCamera, yaw, 0xf8);
	ENSURE_OFFSET(PlayerBehindCamera, pitch, 0x1B8);

	FUNCBIND(calcBehindPosAt, 0265ef90, void (*)(Game::PlayerBehindCamera::PlayerBehindCamera *_this, double param_1, int32_t *param_2, glm::vec3 *param_3, glm::vec3 *param_4, uint32_t *param_5))
	FUNCBIND(calcPosAt, 026655d4, void (*)(Game::PlayerBehindCamera::PlayerBehindCamera *_this))
	}
}
