#pragma once

#include "Game/Macros.h"
#include "StationAddress.h"
#include "InetAddress.h"

namespace nn {
	namespace pia {
		namespace common {
			namespace StationAddress {
				struct StationAddress {
					std::array<char, 0x4> unk1;
					nn::pia::common::InetAddress::InetAddress inetAddress;
				};

				ENSURE_OFFSET(StationAddress, inetAddress, 0x4);
			}
		}
	}
}
