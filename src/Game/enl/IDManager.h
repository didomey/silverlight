#pragma once

#include "Game/Macros.h"
#include "Game/UniqueID.h"

namespace enl {
	namespace IDManager {
		struct IDManager {
			std::array<char, 0x11> unk1;
			byte aid;
			byte playerID;
			byte unk2;
			int32_t idManagersLength;
		};

		ENSURE_OFFSET(IDManager, aid, 0x11);
		ENSURE_OFFSET(IDManager, playerID, 0x12);
		ENSURE_OFFSET(IDManager, idManagersLength, 0x14);

		FUNCBIND(getAIDByUniqueID, 0215b37c, int32_t(*)(enl::IDManager::IDManager* _this, enl::UniqueID* uuid))
		FUNCBIND(getIDInfoByUniqueID, 0215b2a8, IDManager*(*)(enl::IDManager::IDManager* _this, enl::UniqueID* uuid))

		FUNCBIND(isConnectedByAID, 0215bc70, bool(*)(enl::IDManager::IDManager* _this, const char* aid))
		FUNCBIND(isConnected, 0215bb70, bool(*)(enl::IDManager::IDManager* _this, enl::UniqueID* uuid))

		FUNCBIND(disconnectStationInfo, 0215d1f0, void(*)(enl::IDManager::IDManager* _this, enl::UniqueID* uuid))

		FUNCBIND(FUN_0215c8cc, 0215c8cc, void(*)(enl::IDManager::IDManager* _this, int32_t unk))
	}
}
