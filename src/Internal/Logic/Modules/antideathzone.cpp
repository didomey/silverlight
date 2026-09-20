//
// Created by tv on 04.11.23.
//
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>

#include "antideathzone.h"

namespace Modules {
    AntiDeathZone::AntiDeathZone() {
        this->patch = {{0x02644dac, PatchElement("blr", "mflr r0")}};
    }

    bool AntiDeathZone::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AntiDeathZone)
}
