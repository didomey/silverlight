//
// Created by tv on 03.11.23.
//

#pragma once

#include<cstdint>
#include<optional>
#include <glm/vec3.hpp>
#include "Macros.h"
#include<array>

#pragma pack(push, 1)

struct Unk4Unk {
	std::array<char, 0x158> unk1;
	uint32_t m_unk1;
};

ENSURE_OFFSET(Unk4Unk, m_unk1, 0x158);

#pragma pack(pop)

GVARBIND(g_unk4, 101e6474, Unk4Unk*)
