#include "Macros.h"
#include "Player.h"
#include <array>

#pragma once

namespace Game {
	namespace PlayerMgr {
		struct PlayerFactoryIdx {
			uint32_t maxPlayerCount;
			Game::Player::Player** playerActors;
		};

		ENSURE_OFFSET(PlayerFactoryIdx, maxPlayerCount, 0x0);
		ENSURE_OFFSET(PlayerFactoryIdx, playerActors, 0x4);

		struct PlayerFactory {
			PlayerFactoryIdx* playerFactoryIdx;
		};

		ENSURE_OFFSET(PlayerFactory, playerFactoryIdx, 0x0);
	}

	namespace MainMgrBase {
		#pragma pack(push, 1)
		struct PlayerMgr {
			std::array<char, 0x30> unk1;
			Game::PlayerMgr::PlayerFactory* factories;			

			std::array<char, 0x2B8> unk3;
			uint32_t playerCount;
		};

		ENSURE_OFFSET(PlayerMgr, factories, 0x30);
		ENSURE_OFFSET(PlayerMgr, playerCount, 0x2EC);

		struct MainMgrBase {
			std::array<char, 0x268> unk1;
			PlayerMgr* playerMgr;
		};

		ENSURE_OFFSET(MainMgrBase, playerMgr, 0x268);

		#pragma pack(pop)

		GVARBIND(sInstance, 101E2814, MainMgrBase *);

	}
}

