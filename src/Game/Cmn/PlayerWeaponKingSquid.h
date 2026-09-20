#include "Game/Macros.h"
#include "Game/gsys/Model.h"

namespace Cmn {
	namespace PlayerWeaponKingSquid {
		struct PlayerWeaponKingSquid {
			std::array<char, 0x8> unk1;
			gsys::Model::Model* model;

			std::array<char, 0x10> unk2;
			int32_t state;

			std::array<char, 0x3c> unk3;
			int32_t jumpAnimFrm;
		};

		ENSURE_OFFSET(PlayerWeaponKingSquid, model, 0x8);
		ENSURE_OFFSET(PlayerWeaponKingSquid, state, 0x1c);
		ENSURE_OFFSET(PlayerWeaponKingSquid, jumpAnimFrm, 0x5c);



		FUNCBIND(handlePlayerKrakenJumpAnim, 026b947c, void(*)(Cmn::PlayerWeaponKingSquid::PlayerWeaponKingSquid* _this))
		FUNCBIND(attack, 026b9444, void(*)(Cmn::PlayerWeaponKingSquid::PlayerWeaponKingSquid* _this))
		FUNCBIND(updateAnimState, 026b93ac, void(*)(Cmn::PlayerWeaponKingSquid::PlayerWeaponKingSquid* _this))
	}
}
