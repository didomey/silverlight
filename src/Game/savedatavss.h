struct Gear {
	uint32_t hatId;
	uint32_t clotheId;
	uint32_t shoesId;
	uint32_t unk1;
	uint32_t unk2;
	uint32_t unk3;
	uint32_t unk4;
};

FUNCBIND(getCommonPlayerGearId, 021ae004, Gear*(*)(uint32_t* param_1, uint32_t *param_2))

struct Weapon {
	int32_t icon;
	int32_t weaponId;
	int32_t subWeaponId;
	int32_t specialWeaponId;
	int32_t turfInked;
};

FUNCBIND(getPlayerCustomWeaponSetId, 021ae164, Weapon*(*)(int32_t* param_1, int32_t *param_2))

FUNCBIND(getPlayerRank, 021aeac8, uint32_t(*)(int32_t* param_1))
FUNCBIND(getPlayerRankExp, 021aea7c, uint32_t(*)(int32_t* param_1))
FUNCBIND(getUdamaeGrade, 021aeb08, uint32_t(*)(int32_t* param_1))
FUNCBIND(getUdamaePoints, 021aeb48, uint32_t(*)(int32_t* param_1))
FUNCBIND(getMoney, 021aea30, uint32_t(*)(int32_t* param_1))
FUNCBIND(getFestGrade, 021ac11c, uint32_t(*)(int32_t* param_1))
FUNCBIND(getFestPoints, 021ac168, uint32_t(*)(int32_t* param_1))
FUNCBIND(getHopeTeam, 028d540c, uint32_t(*)(int32_t* param_1))
