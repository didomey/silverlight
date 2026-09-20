//
// Created by tv on 04.11.23.
//
#include"antitelemetry.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    AntiTelemetry::AntiTelemetry() {
        this->patch = {
                {0x02009e6c, PatchElement("blr", "mflr r0")},
                {0x0200a7ac, PatchElement("blr", "mflr r0")},
                {0x0200aec4, PatchElement("blr", "mflr r0")},
                {0x0200af0c, PatchElement("blr", "mflr r0")},

                // Prevent DisconnectFromMemoryHash
                {0x020097f0, PatchElement("blr", "mflr r0")}
        };
        this->enablePatch();
    }

    bool AntiTelemetry::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(AntiTelemetry)
}
