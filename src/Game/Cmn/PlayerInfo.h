#pragma once

#include "Game/Macros.h"
#include "Game/Cmn/Def/Gear.h"
#include "Game/Cmn/Def/Weapon.h"
#include <array>

namespace Cmn {
	namespace PlayerInfo {
		struct PlayerInfo {
			uint32_t index;
			int16_t unk;

			short name[17];

			uint32_t country;
			uint32_t area;
			uint32_t team;
			uint32_t gender;
			uint32_t skinTone;
			uint32_t eyeColor;

			// weapon set id
			int32_t fullWeaponId;
			int32_t weaponId;
			int32_t subWeaponId;
			int32_t specialWeaponId;
			int32_t m_unk;

			Cmn::Def::Gear shoes;
			Cmn::Def::Gear clothe;
			Cmn::Def::Gear hat;

			int32_t tankId;
			int32_t rank;
			int32_t rankPoints;
			int32_t festTeam;
			int32_t festId;
			int32_t festGrade;

			std::array<char, 0x10> unk2;
			int32_t pid;

			void setPlayerName(short* name);
		};

		ENSURE_OFFSET(PlayerInfo, index, 0x0);
		ENSURE_OFFSET(PlayerInfo, name, 0x6);
		ENSURE_OFFSET(PlayerInfo, country, 0x28);
		ENSURE_OFFSET(PlayerInfo, area, 0x2c);
		ENSURE_OFFSET(PlayerInfo, team, 0x30);
		ENSURE_OFFSET(PlayerInfo, gender, 0x34);
		ENSURE_OFFSET(PlayerInfo, skinTone, 0x38);
		ENSURE_OFFSET(PlayerInfo, eyeColor, 0x3c);
		ENSURE_OFFSET(PlayerInfo, shoes, 0x54);
		ENSURE_OFFSET(PlayerInfo, clothe, 0x70);
		ENSURE_OFFSET(PlayerInfo, hat, 0x8c);
		ENSURE_OFFSET(PlayerInfo, tankId, 0xa8);
		ENSURE_OFFSET(PlayerInfo, rank, 0xac);
		ENSURE_OFFSET(PlayerInfo, rankPoints, 0xb0);
		ENSURE_OFFSET(PlayerInfo, festTeam, 0xb4);
		ENSURE_OFFSET(PlayerInfo, festId, 0xb8);
		ENSURE_OFFSET(PlayerInfo, festGrade, 0xbc);
		ENSURE_OFFSET(PlayerInfo, pid, 0xd0);

		FUNCBIND(dbgSetRandomValue, 021a728c, void(*)(PlayerInfo* _this, int team))
		FUNCBIND(setPlayerName, 021a6fd0, void(*)(PlayerInfo* _this, void* name))
	}
}
