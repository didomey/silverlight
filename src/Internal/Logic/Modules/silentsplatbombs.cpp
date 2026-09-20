//
// Created by tv on 04.11.23.
//
#include"silentsplatbombs.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    SilentSplatBombs::SilentSplatBombs() {
        this->patch = {
                {0x0269CEBC, PatchElement("li r4, 1", "lbz r4, 0x708(r7)")},
        };
    }

    bool SilentSplatBombs::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(SilentSplatBombs)
}
