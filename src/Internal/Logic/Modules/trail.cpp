//
// Created by tv on 04.11.23.
//
#include"trail.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    Trail::Trail() {
        this->patch = {
                {0x02199A68, PatchElement("li r5, 1", "lwz r5, 0xc(r1)")},
        };
    }

    bool Trail::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(Trail)
}
