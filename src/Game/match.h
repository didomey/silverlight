struct MatchParams {
	std::array<char, 0x4> unk1;
	uint32_t gamemode;
	uint16_t envhour;
	std::array<char, 0x6> unk2;
};

FUNCBIND(setMatchParams, 0217d94c, uint32_t(*)(MatchParams* matchParams, uint32_t* param_2, uint16_t param_3, uint32_t* gamemode, uint16_t* envhour, uint32_t param_6))
