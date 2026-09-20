#include "Game/Cmn/Def/Ability.h"

namespace Cmn {
	namespace Def {
		std::vector<Ability> getAbilitiesFromValue(int value) {
			std::vector<Ability> possibleEnumValues = { Ability::OpeningGambit, Ability::LastDitchEffort, Ability::Tenacity, Ability::Comeback, Ability::ColdBlooded, Ability::NinjaSquid, Ability::Haunt, Ability::Recon, Ability::BombSniffer, Ability::InkResistanceUp, Ability::StealthJump, Ability::DamageUp, Ability::DefenseUp, Ability::InkSaverMain, Ability::InkSaverSub, Ability::InkRecoveryUp, Ability::RunSpeedUp, Ability::SwimSpeedUp, Ability::SpecialChargeUp, Ability::SpecialDurationUp, Ability::QuickRespawn, Ability::SpecialSaver, Ability::QuickSuperJump, Ability::BombRangeUp };

			std::vector<Ability> mainAbilities;

			for (const auto enumValue : possibleEnumValues) {
				int enumValueInt = static_cast<int>(enumValue);
				if (value & enumValueInt) {
					mainAbilities.push_back(enumValue);
					value -= enumValueInt;
				}
			}

			return mainAbilities;
		}

		size_t getAbilityCount(Game::Player::Player* player, Cmn::Def::Ability ability) {
			if (!player->info) return 0;
			if (!player->gearSkillMgr) return 0;

			size_t count = 0;

			std::vector<Ability> mainAbilites = Cmn::Def::getAbilitiesFromValue(player->gearSkillMgr->mainAbilityIds);

			for (const auto mainAbility : mainAbilities) {
				if (ability == mainAbility) {
					count++;
				}
			}

			std::vector<Cmn::Def::Gear> gears = {};

			gears.push_back(player->info->shoes);
			gears.push_back(player->info->clothe);
			gears.push_back(player->info->hat);

			// fuck you c++
			int abilityInt = static_cast<int>(ability);

			for (const auto& gear : gears) {
				std::vector<int32_t> abilities = {};
				abilities.push_back(gear.leftSubAbilityId);
				abilities.push_back(gear.middleSubAbilityId);
				abilities.push_back(gear.rightSubAbilityId);

				for (int i = 0; i < gear.filledAbilitySlotsNum; i++) {
					if (abilities[i] == abilityInt) {
						count++;
					}
				}
			}

			return count;
		}
	}
}
