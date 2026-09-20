//
// Created by tv on 04.11.23.
//
#include"hidedamageoverlay.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    HideDamageOverlay::HideDamageOverlay() {
        this->patch = {
                {0x0268568c, PatchElement("blr", "mflr r0")},
        };
    }

    bool HideDamageOverlay::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(HideDamageOverlay)
}
