//
// Created by tv on 03.11.23.
//

#pragma once

#include<cstdint>
#include<optional>
#include <glm/vec3.hpp>
#include "Macros.h"
#include<array>
#include "PlayerMotion.h"

namespace MainMgrOffset {
    inline const uint32_t PLAYER_1_POS = 0x24c;
}
#pragma pack(push, 1)

struct PlayerBehindCameraUnk {
	std::array<char, 0x23c> m_unk1;
	glm::vec3 m_Hex23CUnk;
};

ENSURE_OFFSET(PlayerBehindCameraUnk, m_Hex23CUnk, 0x23c);

struct PlayerBehindCamera {
	PlayerBehindCameraUnk* m_unk1;

    std::array<char, 0x1B4> Unk1;
    glm::vec3 m_playerMoveRotation;
};

ENSURE_OFFSET(PlayerBehindCamera, m_unk1, 0x0);
ENSURE_OFFSET(PlayerBehindCamera, m_playerMoveRotation, 0x1B8);

struct MainMgrUnk2 {
    std::array<char, 0x540> unk1;
    uint32_t m_chargeState;
};

ENSURE_OFFSET(MainMgrUnk2, m_chargeState, 0x540);

struct MainMgrUnk3 {
    std::array<char, 0x28> unk1;
    float m_damageTaken;
};

ENSURE_OFFSET(MainMgrUnk3, m_damageTaken, 0x28);

struct MainMgrUnk4 {
    int32_t m_unk1;
    int32_t m_unk2;
    int32_t m_unk3;
    int32_t m_unk4;
    int32_t m_unk5;
    int32_t m_unk6;
};

ENSURE_OFFSET(MainMgrUnk4, m_unk1, 0x0);
ENSURE_OFFSET(MainMgrUnk4, m_unk2, 0x4);
ENSURE_OFFSET(MainMgrUnk4, m_unk3, 0x8);
ENSURE_OFFSET(MainMgrUnk4, m_unk4, 0xC);
ENSURE_OFFSET(MainMgrUnk4, m_unk5, 0x10);
ENSURE_OFFSET(MainMgrUnk4, m_unk6, 0x14);

struct MainMgrUnk5 {
    float m_unk1;
};

ENSURE_OFFSET(MainMgrUnk5, m_unk1, 0x0);

// This is actually Player
struct MainMgr {
    std::array<char, 0x2C> unk1;
    uint32_t m_teamId;

    std::array<char, 0x28> m_unk33;
    uint32_t m_isLocalPlayer;

    std::array<char, 0x1C> unk2;
    uint32_t m_weaponId;
    uint32_t m_subWeaponId;
    uint32_t m_specialWeaponId;
    std::array<char, 0x40> unk3;
    uint32_t m_HexC4Unk;
    uint32_t m_hexC8Unk;
    std::array<char, 0x14> unk4;
    uint32_t m_HexE0Unk;
    std::array<char, 0x8> unk5;
    uint32_t m_HexECUnk;
    std::array<char, 0x8> unk6;
    uint32_t m_hexF8Unk;
    std::array<char, 0xD8> unk7;
    uint32_t m_hex1D4Unk;
    // charge release related
    uint32_t m_unk6;
    std::array<char, 0x8> unk8;
    uint32_t m_hex1E4Unk;
    std::array<char, 0x4> unk9;
    uint32_t m_hex1ECUnk;
    uint32_t m_hex1F0Unk;
    std::array<char, 0x54> unk10;
    glm::vec3 m_player1Position;

    std::array<char, 0xF4> unk11;
    float m_Hex348Unk;
    std::array<char, 0x154> unk12;
    float m_Hex4A0Unk;
    float m_Hex4A4Unk;
    std::array<char, 0x4> unk13;
    float m_Hex4ACUnk;
    std::array<char, 0x10> unk14;
    float m_Hex4C0Unk;
    std::array<char, 0x1C> unk15;
    uint32_t m_hex4E0Unk;
    uint32_t m_hex4E4Unk;

    std::array<char, 0xB4> unk24;
    MainMgrUnk5 *m_Hex59CUnk;

    std::array<char, 0x4> unk26;
    uint32_t m_Hex5A4Unk;
    uint32_t m_Hex5A8Unk;
    uint32_t *m_Hex5ACUnk;
    uint32_t m_Hex5B0Unk;
    uint32_t m_Hex5B4Unk;
    uint32_t m_Hex5B8Unk;

    std::array<char, 0x10> unk16;
    uint32_t m_Hex5CCUnk;

    std::array<char, 0x190> unk28;
    MainMgrUnk2 *m_unk2;

    std::array<char, 0x8> unk17;
	Game::PlayerMotion::PlayerMotion* m_playerMotion;

    std::array<char, 0x18> unk21;
    MainMgrUnk3 *m_unk3;

    std::array<char, 0x6c> unk22;
    int m_turfPaint;

    int32_t m_unk8;

    std::array<char, 0x8> unk25;
    int32_t m_unk7;

    std::array<char, 0x80> unk18;

    float m_swimSpeed; //Unsure
    std::array<char, 0x8> unk19;
    uint32_t m_Hex898Unk;
    uint32_t m_Hex89CUnk;
    uint32_t m_Hex8A0Unk;
    uint32_t m_Hex8A4Unk;

    std::array<char, 0x28> unk20;
    PlayerBehindCamera *m_playerBehindCamera;

    std::array<char, 0xAFC> unk23;
    glm::vec3 m_player2Position;

    std::array<char, 0x11F4C4> unk27;
    uint32_t m_unk9;
    uint32_t m_unk10;
};

#pragma pack(pop)

ENSURE_OFFSET(MainMgr, m_teamId, 0x2C);
ENSURE_OFFSET(MainMgr, m_isLocalPlayer, 0x58);
ENSURE_OFFSET(MainMgr, m_weaponId, 0x78);
ENSURE_OFFSET(MainMgr, m_subWeaponId, 0x7C);
ENSURE_OFFSET(MainMgr, m_specialWeaponId, 0x80);
ENSURE_OFFSET(MainMgr, m_hexC8Unk, 0xC8);
ENSURE_OFFSET(MainMgr, m_HexC4Unk, 0xC4);
ENSURE_OFFSET(MainMgr, m_HexE0Unk, 0xE0);
ENSURE_OFFSET(MainMgr, m_HexECUnk, 0xEC);
ENSURE_OFFSET(MainMgr, m_hexF8Unk, 0xF8);
ENSURE_OFFSET(MainMgr, m_hex1D4Unk, 0x1D4);
ENSURE_OFFSET(MainMgr, m_unk6, 0x1D8);
ENSURE_OFFSET(MainMgr, m_hex1E4Unk, 0x1E4);
ENSURE_OFFSET(MainMgr, m_hex1ECUnk, 0x1EC);
ENSURE_OFFSET(MainMgr, m_hex1F0Unk, 0x1F0);
ENSURE_OFFSET(MainMgr, m_player1Position, 0x248);
ENSURE_OFFSET(MainMgr, m_Hex348Unk, 0x348);
ENSURE_OFFSET(MainMgr, m_Hex4A0Unk, 0x4A0);
ENSURE_OFFSET(MainMgr, m_Hex4A4Unk, 0x4A4);
ENSURE_OFFSET(MainMgr, m_Hex4ACUnk, 0x4AC);
ENSURE_OFFSET(MainMgr, m_Hex4C0Unk, 0x4C0);
ENSURE_OFFSET(MainMgr, m_hex4E0Unk, 0x4E0);
ENSURE_OFFSET(MainMgr, m_hex4E4Unk, 0x4E4);
ENSURE_OFFSET(MainMgr, m_Hex59CUnk, 0x59C);
ENSURE_OFFSET(MainMgr, m_Hex5A4Unk, 0x5A4);
ENSURE_OFFSET(MainMgr, m_Hex5A8Unk, 0x5A8);
ENSURE_OFFSET(MainMgr, m_Hex5ACUnk, 0x5AC);
ENSURE_OFFSET(MainMgr, m_Hex5B0Unk, 0x5B0);
ENSURE_OFFSET(MainMgr, m_Hex5B4Unk, 0x5B4);
ENSURE_OFFSET(MainMgr, m_Hex5B8Unk, 0x5B8);
ENSURE_OFFSET(MainMgr, m_Hex5CCUnk, 0x5CC);
ENSURE_OFFSET(MainMgr, m_unk2, 0x760);
ENSURE_OFFSET(MainMgr, m_playerMotion, 0x76C);
ENSURE_OFFSET(MainMgr, m_unk3, 0x788);
ENSURE_OFFSET(MainMgr, m_turfPaint, 0x7F8);
ENSURE_OFFSET(MainMgr, m_unk8, 0x7FC);
ENSURE_OFFSET(MainMgr, m_unk7, 0x808);
ENSURE_OFFSET(MainMgr, m_swimSpeed, 0x88C);
ENSURE_OFFSET(MainMgr, m_Hex898Unk, 0x898);
ENSURE_OFFSET(MainMgr, m_Hex89CUnk, 0x89C);
ENSURE_OFFSET(MainMgr, m_Hex8A0Unk, 0x8A0);
ENSURE_OFFSET(MainMgr, m_Hex8A4Unk, 0x8A4);
ENSURE_OFFSET(MainMgr, m_playerBehindCamera, 0x8D0);
ENSURE_OFFSET(MainMgr, m_player2Position, 0x13D0);

[[deprecated("Use the g_mainMgr global instead")]]
MainMgr *getMainMgr();

GVARBIND(g_playerMgr, 101e16e8, MainMgr *)

namespace Game {
	namespace PlayerMgr {
		GVARBIND(sInstance, 101e16e8, MainMgr *)
	}
}
