//
// Created by tv on 04.11.23.
//
#include"recontimerbypass.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    ReconTimerBypass::ReconTimerBypass() {
        this->patch = {{0x02762c14, PatchElement("nop", "subi r11, r11, 0x1")}};
		this->enablePatch();
    }

    bool ReconTimerBypass::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(ReconTimerBypass)
}
