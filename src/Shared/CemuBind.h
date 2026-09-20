#pragma once

#include "BindUtil.h"
#include "Game/Cmn/PlayerInfo.h"

extern void (*SLInvalidateCache)(uint32_t begin, uint32_t end);
extern void* (*SLInternalNetGetState)(void);
extern void (*SLInternalNetLogMatch)(void* state, uint32_t session_id, uint8_t player_index, Cmn::PlayerInfo::PlayerInfo player_info, const uint32_t* flags, std::size_t flagsSize);

void LoadCemuSLSymbols();
