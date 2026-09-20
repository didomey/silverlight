#pragma once

#include "Game/Macros.h"
#include "Game/nn/pia/common/StationAddress.h"

namespace nn {
	namespace pia {
		namespace transport {
			namespace StationLocation {
				struct StationLocation {
					std::array<char, 0x4> unk1;
					nn::pia::common::StationAddress::StationAddress stationAddress;
					std::array<char, 0x8> unk2;
					int32_t principalId;
				};

				ENSURE_OFFSET(StationLocation, stationAddress, 0x4);
				ENSURE_OFFSET(StationLocation, principalId, 0x18);

				FUNCBIND(StationLocationCtor, 02caf5d0, void(*)(nn::pia::transport::StationLocation::StationLocation* _this))
			}
		}
	}
}
