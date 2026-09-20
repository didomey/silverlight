//
// Created by tv on 03.11.23.
//

#pragma once

#include<cstdint>
#include<optional>
#include <glm/vec3.hpp>
#include "Macros.h"
#include<array>


inline const uint32_t UNK_PTR = 0x101E09C8;

#pragma pack(push, 1)

struct UnkUnk2 {
	std::array<char, 0x5c> unk1;
	uint16_t m_connectedPlayers;
	std::array<char, 0x2> unk2;
	uint32_t m_playersJoined;
	uint32_t m_playersInLobby;
	std::array<char, 0x9> unk3;
	bool m_shouldStartMatch;
};

ENSURE_OFFSET(UnkUnk2, m_connectedPlayers, 0x5c);
ENSURE_OFFSET(UnkUnk2, m_playersJoined, 0x60);
ENSURE_OFFSET(UnkUnk2, m_playersInLobby, 0x64);
ENSURE_OFFSET(UnkUnk2, m_shouldStartMatch, 0x71);

struct UnkUnk1 {
	std::array<char, 0x270> unk1;
	UnkUnk2* m_unk1;
};

ENSURE_OFFSET(UnkUnk1, m_unk1, 0x270);

// Note: never use PascalCase for unk fields under any circumstances
class UnkUnk {
public:
    std::array<char, 0x278> unk1;
	UnkUnk1* m_unk1;
};

ENSURE_OFFSET(UnkUnk, m_unk1, 0x278);

#pragma pack(pop)

UnkUnk* getUnk();

GVARBIND(g_unk, 101E09C8, UnkUnk*)
