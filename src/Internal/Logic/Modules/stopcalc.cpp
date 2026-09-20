//
// Created by tv on 04.11.23.
//
#include"stopcalc.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    StopCalc::StopCalc() {
        this->patch = {
            {0x0223586c, PatchElement("blr", "stwu r1, -0x38(r1)")}
        };
    }

    bool StopCalc::isCheatModule() {
		return true;
    }

    REGISTERVCLASS(StopCalc)
}
