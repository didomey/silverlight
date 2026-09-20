//
// Created by tv on 04.11.23.
//
#include"nodaychangedisp.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    NoDayChangeDisp::NoDayChangeDisp() {
		this->patchLine(0x021b7fdc, "li r4, 0x0");
        this->enablePatch();
    }

    bool NoDayChangeDisp::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(NoDayChangeDisp)
}
