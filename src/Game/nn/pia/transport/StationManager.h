#pragma once

#include "Game/Macros.h"
#include "Station.h"

namespace nn {
	namespace pia {
		namespace transport {
			namespace StationManager {
				struct StationManager {
					std::array<char, 0x34> unk1;
					int32_t stationsLength;
					nn::pia::transport::Station::Station** stations;
				};

				ENSURE_OFFSET(StationManager, stationsLength, 0x34);
				ENSURE_OFFSET(StationManager, stations, 0x38);

				FUNCBIND(GetStation, 02cb6d7c, nn::pia::transport::Station::Station*(*)(nn::pia::transport::StationManager::StationManager* _this, int32_t stationIdx))
				FUNCBIND(DisconnectStation, 02c25a84, int32_t(*)(nn::pia::transport::StationManager::StationManager* _this, int32_t stationIdx))

				GVARBIND(s_pInstance, 101e8988, nn::pia::transport::StationManager::StationManager*)
			}
		}
	}
}
