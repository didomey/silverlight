#pragma once

#include "Game/Macros.h"
#include "Station.h"
#include "StationConnectionInfo.h"

namespace nn {
	namespace pia {
		namespace transport {
			namespace StationConnectionInfoTable {
				struct StationConnectionInfoFactory {
					nn::pia::transport::StationConnectionInfo::StationConnectionInfo** stationConnInfos;
				};

				ENSURE_OFFSET(StationConnectionInfoFactory, stationConnInfos, 0x0);

				struct StationConnectionInfoTable {
					std::array<char, 0xe8> unk1;
					nn::pia::transport::StationConnectionInfo::StationConnectionInfo** stationConnInfos;

					std::array<char, 0x80> unk2;
					uint32_t stationConnInfosLength;
				};

				ENSURE_OFFSET(StationConnectionInfoTable, stationConnInfos, 0xe8);
				ENSURE_OFFSET(StationConnectionInfoTable, stationConnInfosLength, 0x16c);

				FUNCBIND(GetStationConnectionInfo, 02cbb00c, int32_t(*)(nn::pia::transport::StationConnectionInfoTable::StationConnectionInfoTable* _this, nn::pia::transport::Station::Station* station, nn::pia::transport::StationConnectionInfo::StationConnectionInfo* connInfo))

				GVARBIND(s_pInstance, 101e899c, nn::pia::transport::StationConnectionInfoTable::StationConnectionInfoTable*)
			}
		}
	}
}
