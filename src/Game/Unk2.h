//
// Created by tv on 03.11.23.
//

#pragma once

#include<cstdint>
#include<optional>
#include <glm/vec3.hpp>
#include "Macros.h"
#include<array>

inline const uint32_t UNK2_PTR = 0x101E117C;

#pragma pack(push, 1)

// Rapid fire related
struct Unk2Unk3 {
	// Shooter Blaster
	std::array<char, 0x30> unk1;
	uint32_t m_unk3;

	std::array<char, 0x1C> unk6;
	uint32_t m_unk10;

	// Charger
	std::array<char, 0x1C> unk2;
	uint32_t m_unk1;
	uint32_t m_unk2;

	// Splatling (Spinner)
	std::array<char, 0x10> unk5;
	uint32_t m_unk7;
	uint32_t m_unk8;
	uint32_t m_unk9;

	// Roller
	std::array<char, 0x1c> unk3;
	uint32_t m_unk4;
	uint32_t m_unk5;

	// Slosher
	std::array<char, 0xC0> unk4;
	uint32_t m_unk6;
};

ENSURE_OFFSET(Unk2Unk3, m_unk3, 0x30);
ENSURE_OFFSET(Unk2Unk3, m_unk10, 0x50);
ENSURE_OFFSET(Unk2Unk3, m_unk1, 0x70);
ENSURE_OFFSET(Unk2Unk3, m_unk2, 0x74);
ENSURE_OFFSET(Unk2Unk3, m_unk7, 0x88);
ENSURE_OFFSET(Unk2Unk3, m_unk8, 0x8C);
ENSURE_OFFSET(Unk2Unk3, m_unk9, 0x90);
ENSURE_OFFSET(Unk2Unk3, m_unk4, 0xB0);
ENSURE_OFFSET(Unk2Unk3, m_unk5, 0xB4);
ENSURE_OFFSET(Unk2Unk3, m_unk6, 0x178);

struct Unk2Unk2 {
	std::array<char, 0x760> unk1;
	Unk2Unk3* m_unk1;
};

ENSURE_OFFSET(Unk2Unk2, m_unk1, 0x760);

class Unk2Unk {
public:
	std::array<char, 0x578> unk1;
	Unk2Unk2* m_unk1;
};

ENSURE_OFFSET(Unk2Unk, m_unk1, 0x578);

#pragma pack(pop)

Unk2Unk* getUnk2();
