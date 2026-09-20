#pragma once

#include "Game/Macros.h"
#include "StationLocation.h"

namespace nn {
	namespace pia {
		namespace transport {
			namespace StationConnectionInfo {
				struct StationConnectionInfo {
					std::array<char, 0x4> unk1;
					nn::pia::transport::StationLocation::StationLocation stationLocation;
				};

				ENSURE_OFFSET(StationConnectionInfo, stationLocation, 0x4);

				FUNCBIND(StationConnectionInfoCtor, 02caf650, void(*)(nn::pia::transport::StationConnectionInfo::StationConnectionInfo* _this))
			}
		}
	}
}
