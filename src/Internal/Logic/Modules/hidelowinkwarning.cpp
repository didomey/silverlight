//
// Created by tv on 04.11.23.
//
#include"hidelowinkwarning.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    HideLowInkWarning::HideLowInkWarning() {
        this->patch = {
                {0x0248c8d4, PatchElement("blr", "stwu r1, -0x20(r1)")},
                {0x026d46f4, PatchElement("blr", "mflr r0")},
        };
    }

    bool HideLowInkWarning::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(HideLowInkWarning)
}
