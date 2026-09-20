//
// Created by tv on 04.11.23.
//
#include"save.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include "Game/savedatavss.h"
#include "InputModule.h"

static uint32_t level = 0;
static uint32_t levelExp = 0;
static uint32_t rank = 0;
static uint32_t rankPoints = 0;
static uint32_t money = 0;
static uint32_t festRank = 0;
static uint32_t festRankPoints = 0;
static uint32_t festTeam = 0;

uint32_t save_repl_getPlayerRank(int32_t *param_1) {
    return level;
}

uint32_t save_repl_getPlayerRankExp(int32_t *param_1) {
    return levelExp;
}

uint32_t save_repl_getUdamaeGrade(int32_t *param_1) {
    return rank;
}

uint32_t save_repl_getUdamaePoints(int32_t *param_1) {
    return rankPoints;
}

uint32_t save_repl_getMoney(int32_t *param_1) {
    return money;
}

uint32_t save_repl_getFestGrade(int32_t *param_1) {
    return festRank;
}

uint32_t save_repl_getFestPoints(int32_t *param_1) {
    return festRankPoints;
}

uint32_t save_repl_getHopeTeam(int32_t *param_1) {
    return festTeam;
}

namespace Modules {
	void CustomLevelInput::receivedEntry(const std::u16string &input) {
		level = toUnsignedInt(input) - 1;
    }

	REGISTERVCLASS(CustomLevelInput)

    CustomLevel::CustomLevel() {
        this->patch = {
			{0x021aeac8, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void *) save_repl_getPlayerRank, 0x021aeac8), "mflr r0")},
        };
    }

    bool CustomLevel::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(CustomLevel)

	void CustomLevelExpInput::receivedEntry(const std::u16string &input) {
		levelExp = toUnsignedInt(input) - 1;
    }

	REGISTERVCLASS(CustomLevelExpInput)

    CustomLevelExp::CustomLevelExp() {
        this->patch = {
			{0x021aea7c, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void *) save_repl_getPlayerRankExp, 0x021aea7c), "mflr r0")},
        };
    }

    bool CustomLevelExp::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(CustomLevelExp)

	void CustomRankInput::receivedEntry(const std::u16string &input) {
		rank = toUnsignedInt(input) - 1;
    }

	REGISTERVCLASS(CustomRankInput)

    CustomRank::CustomRank() {
        this->patch = {
			{0x021aeb08, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void *) save_repl_getUdamaeGrade, 0x021aeb08), "mflr r0")},
        };
    }

    bool CustomRank::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(CustomRank)

	void CustomRankPointsInput::receivedEntry(const std::u16string &input) {
		rankPoints = toUnsignedInt(input) - 1;
    }

	REGISTERVCLASS(CustomRankPointsInput)

    CustomRankPoints::CustomRankPoints() {
        this->patch = {
			{0x021aeb48, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void *) save_repl_getUdamaePoints, 0x021aeb48), "mflr r0")},
        };
    }

    bool CustomRankPoints::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(CustomRankPoints)

	void CustomMoneyInput::receivedEntry(const std::u16string &input) {
		money = toUnsignedInt(input) - 1;
    }

	REGISTERVCLASS(CustomMoneyInput)

    CustomMoney::CustomMoney() {
        this->patch = {
			{0x021aea30, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void *) save_repl_getMoney, 0x021aea30), "mflr r0")},
        };
    }

    bool CustomMoney::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(CustomMoney)

	void CustomFestRankInput::receivedEntry(const std::u16string &input) {
		money = toUnsignedInt(input) - 1;
    }

	REGISTERVCLASS(CustomFestRankInput)

    CustomFestRank::CustomFestRank() {
        this->patch = {
			{0x021ac11c, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void *) save_repl_getFestGrade, 0x021ac11c), "mflr r0")},
        };
    }

    bool CustomFestRank::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(CustomFestRank)

	void CustomFestRankPointsInput::receivedEntry(const std::u16string &input) {
		festRankPoints = toUnsignedInt(input) - 1;
    }

	REGISTERVCLASS(CustomFestRankPointsInput)

    CustomFestRankPoints::CustomFestRankPoints() {
        this->patch = {
			{0x021ac168, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void *) save_repl_getFestPoints, 0x021ac168), "mflr r0")},
        };
    }

    bool CustomFestRankPoints::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(CustomFestRankPoints)

	void CustomFestTeamInput::receivedEntry(const std::u16string &input) {
		festTeam = toUnsignedInt(input) - 1;
    }

	REGISTERVCLASS(CustomFestTeamInput)

    CustomFestTeam::CustomFestTeam() {
        this->patch = {
			{0x028d540c, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void *) save_repl_getHopeTeam, 0x028d540c), "mflr r0")},
        };
    }

    bool CustomFestTeam::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(CustomFestTeam)
}
