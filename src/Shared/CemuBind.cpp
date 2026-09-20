#include "CemuBind.h"
#include<coreinit/dynload.h>
#include "Game/Cmn/PlayerInfo.h"

void (*SLInvalidateCache)(uint32_t begin, uint32_t end);
void* (*SLInternalNetGetState)(void);
void (*SLInternalNetLogMatch)(void* state, uint32_t session_id, uint8_t player_index, Cmn::PlayerInfo::PlayerInfo player_info, const uint32_t* flags, std::size_t flags_size);

void LoadCemuSLSymbols() {
    OSDynLoad_Module coreinit;
    OSDynLoad_Acquire("coreinit", &coreinit);

	LOAD_FUNC(coreinit, SLInvalidateCache);
	LOAD_FUNC(coreinit, SLInternalNetGetState);
	LOAD_FUNC(coreinit, SLInternalNetLogMatch);
}
