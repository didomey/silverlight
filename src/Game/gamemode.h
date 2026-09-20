struct GamemodeInfo {
	std::string name;
	uint32_t id;
};

inline std::array<GamemodeInfo, 5> gamemodes = {
	{
    	//{"cNone", -1},
        {"Turf War", 0},
        {"Splat Zones", 2},
        {"Tower Control", 3},
        {"Rainmaker", 1},
	}
};
