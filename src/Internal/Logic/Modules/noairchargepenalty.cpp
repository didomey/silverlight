//
// Created by tv on 04.11.23.
//
#include"noairchargepenalty.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include "Game/Player.h"

namespace Modules {
    NoAirChargePenalty::NoAirChargePenalty() {
        this->patch = {
                {0x02698C10, PatchElement("li r3, 0", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::Player::isAerial, 0x02698C10))},
                {0x02699040, PatchElement("li r3, 0", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::Player::isAerial, 0x02699040))},
        };
    }

    bool NoAirChargePenalty::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(NoAirChargePenalty)
}
