//
// Created by tv on 04.11.23.
//
#include"noplayerhitboxcollision.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    NoPlayerHitboxCollision::NoPlayerHitboxCollision() {
        this->patch = {
                {0x02033948, PatchElement("li r3, 0", "li r3, 1")},
        };
    }

    bool NoPlayerHitboxCollision::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(NoPlayerHitboxCollision)
}
