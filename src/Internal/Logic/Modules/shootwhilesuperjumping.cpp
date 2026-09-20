//
// Created by tv on 04.11.23.
//
#include"shootwhilesuperjumping.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    ShootWhileSuperjumping::ShootWhileSuperjumping() {
        this->patch = {
                {0x02631534, PatchElement("li r3, 0", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x026314b4, 0x02631534))},
        };
    }

    bool ShootWhileSuperjumping::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(ShootWhileSuperjumping)
}
