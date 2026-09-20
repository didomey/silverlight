//
// Created by tv on 04.11.23.
//
#include"superjumpwithrainmaker.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    SuperjumpWithRainmaker::SuperjumpWithRainmaker() {
        this->patch = {
                {0x02653E30, PatchElement("li r0, 0", "lbz r0, 0x708(r31)")},
        };
    }

    bool SuperjumpWithRainmaker::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(SuperjumpWithRainmaker)
}
