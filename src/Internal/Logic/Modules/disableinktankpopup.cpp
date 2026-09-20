//
// Created by tv on 04.11.23.
//
#include"disableinktankpopup.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    DisableInkTankPopup::DisableInkTankPopup() {
		this->patchLine(0x02692390, "nop");
    }

    bool DisableInkTankPopup::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DisableInkTankPopup)
}
