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

struct Unk3Unk3 {
	std::array<char, 0x1C8> unk1;
	uint32_t m_unk1;

	std::array<char, 0x60> unk2;
	uint32_t m_unk2;

	uint32_t m_unk3;

	uint32_t m_unk4;
};

ENSURE_OFFSET(Unk3Unk3, m_unk1, 0x1C8);
ENSURE_OFFSET(Unk3Unk3, m_unk2, 0x22C);
ENSURE_OFFSET(Unk3Unk3, m_unk3, 0x230);
ENSURE_OFFSET(Unk3Unk3, m_unk4, 0x234);

struct Unk3Unk2 {
	std::array<char, 0x2B8> unk1;
	Unk3Unk3* m_unk1;
};

ENSURE_OFFSET(Unk3Unk2, m_unk1, 0x2B8);

struct Unk3Unk {
	std::array<char, 0x3A4> unk1;
	Unk3Unk2* m_unk1;
};

ENSURE_OFFSET(Unk3Unk, m_unk1, 0x3A4);

#pragma pack(pop)

GVARBIND(g_unk3, 101F4B00, Unk3Unk*)
