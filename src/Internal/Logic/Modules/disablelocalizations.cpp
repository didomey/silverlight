//
// Created by tv on 04.11.23.
//
#include"disablelocalizations.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include <coreinit/memory.h>

namespace Modules {
    DisableLocalizations::DisableLocalizations() {
        this->patch = {
                {0x028c9308, PatchElement("blr", "mr r11, r3")},
        };
    }

    bool DisableLocalizations::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DisableLocalizations)
}
