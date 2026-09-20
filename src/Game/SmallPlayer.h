		struct Player {
			std::array<char, 0x2C> unk1;
			uint32_t teamId;

			std::array<char, 0x28> unk29;
			uint32_t isLocalPlayer;

			std::array<char, 0x6> unk36;
			uint16_t shotBulletsNum;

			std::array<char, 0x14> unk2;
			uint32_t weaponId;

			uint32_t subWeaponId;
			uint32_t specialWeaponId;

			std::array<char, 0x20> unk41;
			int32_t info;

			std::array<char, 0x1c> unk3;
			bool isReceiveUnk1;
			bool isReceiveJump;
			bool isReceiveUnk2;
			bool isReceiveUnk3;
			bool isReceiveUnk4;
			bool isReceiveUnk5;
			bool isReceiveUnk6;
			bool isReceiveUnk7;

			std::array<char, 0xC> unk31;
			uint16_t isShooting;
			uint32_t isSubWeaponHeld;

			bool isReqHoldBombNoControl;
			bool isReqHoldBombNoControl2;
			bool isReqThrowBomb;
			bool isReqHoldBomb;

			std::array<char, 0xa> unk5;
			uint32_t hexECUnk;
			std::array<char, 0x8> unk6;
			uint32_t useSubDelayFrm;
			bool isSwimming;
			bool isSwimming_;

			std::array<char, 0x52> unk46;
			int32_t curPlayerFrm;
			int32_t curPlayerFrm2;

			std::array<char, 0x7c> unk7;
			uint32_t hex1D4Unk;
			// charge release related
			uint32_t m_unk6;
			std::array<char, 0x8> unk8;
			uint32_t hex1E4Unk;
			std::array<char, 0x4> unk9;
			uint32_t hex1ECUnk;
			uint32_t hex1F0Unk;
		};

