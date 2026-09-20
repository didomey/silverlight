//
// Created by tv on 04.11.23.
//
#include"invisibility.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    Invisibility::Invisibility() {
        this->patch = {
                {0x026579c8, PatchElement("blr", "mflr r0")},
        };
    }

    bool Invisibility::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(Invisibility)
}
