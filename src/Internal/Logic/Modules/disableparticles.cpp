//
// Created by tv on 04.11.23.
//
#include"disableparticles.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    DisableParticles::DisableParticles() {
        this->patch = {
                {0x02b25474, PatchElement("li r3, 0", "li r3, 1")},
        };
    }

    bool DisableParticles::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DisableParticles)
}
