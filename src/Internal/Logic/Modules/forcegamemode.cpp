//
// Created by tv on 04.11.23.
//
#include"forcegamemode.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include"Game/gamemode.h"
#include"Game/match.h"
#include "Game/savedatavss.h"
#include "InputModule.h"
#include "Internal/silverlight.h"

void repl_setMatchParams(MatchParams* matchParams, uint32_t* param_2, uint16_t param_3, uint32_t* gamemode, uint16_t* envhour, uint32_t param_6) {
	Modules::ForceGamemodeInput *forceGamemodeInputModule = silverlightInstance->m_moduleStates.getModule<Modules::ForceGamemodeInput>();

	setMatchParams(matchParams, param_2, param_3, &forceGamemodeInputModule->gamemode, envhour, param_6);
}

namespace Modules {
	void ForceGamemodeInput::receivedEntry(const std::u16string &input) {
		GamemodeInfo &closestMatch = findClosestMatch<GamemodeInfo>(u16string_to_string(input), gamemodes,
            [](const GamemodeInfo &info) -> std::string {
            return info.name;
        });

		this->gamemode = closestMatch.id;
    }

	REGISTERVCLASS(ForceGamemodeInput)

    ForceGamemode::ForceGamemode() {
        this->patch = {
			{0x02159db8, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setMatchParams, 0x02159db8), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setMatchParams, 0x02159db8))},
			{0x02166ee4, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setMatchParams, 0x02166ee4), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setMatchParams, 0x02166ee4))},
			{0x0216eaf8, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setMatchParams, 0x0216eaf8), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setMatchParams, 0x0216eaf8))},
			{0x0217601c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setMatchParams, 0x0217601c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setMatchParams, 0x0217601c))},
			{0x0217b130, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_setMatchParams, 0x0217b130), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) setMatchParams, 0x0217b130))},
        };
    }

    bool ForceGamemode::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(ForceGamemode)
}
