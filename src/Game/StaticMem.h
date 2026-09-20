//
// Created by tv on 03.11.23.
//

#pragma once

#include<cstdint>
#include<optional>
#include <glm/vec3.hpp>
#include "Macros.h"
#include<array>

#include "Cmn/Mode.h"
#include "Cmn/Rule.h"

inline const uint32_t STATIC_MEM_PTR = 0x101dd330;

#pragma pack(push, 1)

namespace Cmn {
	namespace StaticMem {
		class StaticMem {
		public:
			std::array<char, 0x1C> unk1;
			char *m_mapName;
			std::array<char, 0x214> unk2;
			int32_t m_hour;
			Cmn::Mode m_mode;
			Cmn::Rule rule;
			int32_t m_bgmId;
			int32_t m_bgmSeed;

			std::array<char, 0x20> unk4;
			int32_t m_password;

			std::array<char, 0x1CB> unk5;
			// Unsure
			bool m_isSquidLabResearcher;
		};

#pragma pack(pop)

		ENSURE_OFFSET(StaticMem, m_mapName, 0x1c);
		ENSURE_OFFSET(StaticMem, m_hour, 0x234);
		ENSURE_OFFSET(StaticMem, m_mode, 0x238);
		ENSURE_OFFSET(StaticMem, rule, 0x23c);
		ENSURE_OFFSET(StaticMem, m_bgmId, 0x240);
		ENSURE_OFFSET(StaticMem, m_bgmSeed, 0x244);
		ENSURE_OFFSET(StaticMem, m_password, 0x268);
		ENSURE_OFFSET(StaticMem, m_isSquidLabResearcher, 0x437);
		
		GVARBIND(sInstance, 101dd330, Cmn::StaticMem::StaticMem*)
	}
}

[[deprecated("Use the g_staticMem global instead")]]
Cmn::StaticMem::StaticMem *getStaticMem();

GVARBIND(g_staticMem, 101dd330, Cmn::StaticMem::StaticMem*)
