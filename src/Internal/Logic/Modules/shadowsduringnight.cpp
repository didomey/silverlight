//
// Created by tv on 04.11.23.
//
#include"shadowsduringnight.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    ShadowsDuringNight::ShadowsDuringNight() {
        this->patch = {
                {0x0242ABB4, PatchElement("nop", "stb r28, 0x4a0(r7)")},
                {0x0242ABC0, PatchElement("nop", "stb r28, 0x4c0(r8)")},
                {0x0242ABCC, PatchElement("nop", "stb r28, 0x530(r9)")},
        };
    }

    bool ShadowsDuringNight::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(ShadowsDuringNight)
}
