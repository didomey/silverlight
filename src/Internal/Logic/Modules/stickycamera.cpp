//
// Created by tv on 04.11.23.
//
#include"stickycamera.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>
#include <coreinit/memory.h>
#include "Game/Player.h"

namespace Modules {
    StickyCamera::StickyCamera() {
        this->patch = {
                {0x02665d38, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::Player::getJumpVelRatio, 0x02665d38))},
        };
    }

    bool StickyCamera::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(StickyCamera)
}
