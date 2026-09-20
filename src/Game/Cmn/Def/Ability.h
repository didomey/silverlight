#pragma once

#include "Game/Macros.h"

#include <vector>
#include <unordered_set>

#include "Game/Player.h"

#include "Game/Cmn/Def/Gear.h"

namespace Cmn {
	namespace Def {
		enum class Ability {
			OpeningGambit = 0x001,
			LastDitchEffort = 0x002,
			Tenacity = 0x004,
			Comeback = 0x008,
			ColdBlooded = 0x010,
			NinjaSquid = 0x020,
			Haunt =	0x040,
			Recon =	0x080,
			BombSniffer = 0x100,
			InkResistanceUp = 0x200,
			StealthJump = 0x400,
			Unused = 0x800,

			DamageUp = 0,
			DefenseUp = 1,
			InkSaverMain = 2,
			InkSaverSub = 3,
			InkRecoveryUp = 4,
			RunSpeedUp = 5,
			SwimSpeedUp = 6,
			SpecialChargeUp = 7,
			SpecialDurationUp = 8,
			QuickRespawn = 9,
			SpecialSaver = 10,
			QuickSuperJump = 11,
			BombRangeUp = 12,
		};

		const std::unordered_set<Cmn::Def::Ability> mainAbilities = { Ability::OpeningGambit, Ability::LastDitchEffort, Ability::Tenacity, Ability::Comeback, Ability::ColdBlooded, Ability::NinjaSquid, Ability::Haunt, Ability::Recon, Ability::BombSniffer, Ability::InkResistanceUp, Ability::StealthJump, Ability::Unused };

		std::vector<Ability> getAbilitiesFromValue(int value);
		size_t getAbilityCount(Cmn::Def::Ability ability);
	}
}
