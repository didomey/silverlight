#pragma once

#include "Game/Macros.h"
#include "Game/UniqueID.h"
#include "IDManager.h"

namespace enl {
	namespace PeerManagerCommon {
		struct PeerManagerCommon {
			std::array<char, 0x84> unk1;
			enl::IDManager::IDManager* idManager;
		};

		ENSURE_OFFSET(PeerManagerCommon, idManager, 0x84);

		FUNCBIND(getPlayerIDByUniqueID, 0215a818, int32_t(*)(enl::PeerManagerCommon::PeerManagerCommon* _this, enl::UniqueID* uuid))
	}
}
