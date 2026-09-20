//
// Created by tv on 04.11.23.
//
#include"futurefly.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

#include "playeresp.h"

namespace Modules {
    PlayerEsp::PlayerEsp() {
        this->patch = {
                {0x02684440, PatchElement("addic. r16, r16, 0x63E", "clrlwi r16, r16, 24")},
                {0x0268445c, PatchElement("cmpwi r16, 0x1", "cmpwi r16, 0x0")}
        };
    }

    bool PlayerEsp::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(PlayerEsp)
}

