//
// Created by tv on 04.11.23.
//
#include"antidc.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    AntiDC::AntiDC() {
        this->patch = {
                {0x0263682C, PatchElement("li r3, 0", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x0274c4d0, 0x0263682C))},
				{0x02753FC8, PatchElement("li r0, 0x1", "lwz r0, 0x10(r11)")}
        };
        this->enablePatch();
    }

    bool AntiDC::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(AntiDC)
}
