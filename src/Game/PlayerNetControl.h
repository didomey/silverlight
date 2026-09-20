#pragma once

#include "Game/Macros.h"
#include <glm/vec3.hpp>
#include <array>
#include "Player.h"
#include "Game/PlayerNetState.h"

struct Ability {
	int mainAbility;
	int firstAbility;
	int secondAbility;
	int thirdAbility;
};

namespace Game {
	namespace Player {
		struct Player;
	}

	namespace PlayerNetControl {
		#pragma pack(push, 1)
		struct PlayerNetControl {
			Game::Player::Player* playerRef;

			std::array<char, 0x110> unk1;
			int* netRecvData;
			std::array<char, 0x4> unk2;
			uint32_t newNetDataEmpty;

			std::array<char, 0x8d8> unk3;
			int32_t jumpFinished;
		};
		#pragma pack(pop)

		ENSURE_OFFSET(PlayerNetControl, playerRef, 0x0);
		ENSURE_OFFSET(PlayerNetControl, netRecvData, 0x114);
		ENSURE_OFFSET(PlayerNetControl, newNetDataEmpty, 0x11c);
		ENSURE_OFFSET(PlayerNetControl, jumpFinished, 0x9f8);

		FUNCBIND(receiveData, 026cb754, int32_t(*)(Game::PlayerNetControl::PlayerNetControl* _this, Game::PlayerNetState::PlayerNetState* playerNetState, uint32_t state))
		FUNCBIND(calcReceive, 026ca810, void(*)(Game::PlayerNetControl::PlayerNetControl* _this))

		FUNCBIND(sendEvent_StartBarrier, 026cb9e4, int32_t(*)(Game::PlayerNetControl::PlayerNetControl* _this, uint32_t unk))
		FUNCBIND(sendEvent_Revival, 026cb978, int32_t(*)(Game::PlayerNetControl::PlayerNetControl* _this, glm::vec3* param_1, glm::vec3* param_2, int param_3, int param_4))
		FUNCBIND(sendEvent_StartSuperLanding, 026cb99c, void(*)(Game::PlayerNetControl::PlayerNetControl* _this, uint32_t *unk))
	}
}
