#include "match.h"
#include <cstdint>

void MatchParams::set(int32_t* unk1, short map, uint32_t* gamemode, uint32_t* envHour, uint32_t unk2) {
	this->map = map;
	this->m_unk1 = (int16_t)*unk1;
	this->gamemode = gamemode;
	this->m_unk2 = unk2;
	this->envHour = (short)*envHour;
}
