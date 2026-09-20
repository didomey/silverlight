//
// Created by tv on 04.11.23.
//
#include"bgmecho.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include <coreinit/memory.h>

namespace Modules {
    BGMEcho::BGMEcho() {
        this->patch = {
            {0x021D1694, PatchElement("li r3, 1", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x021d5c50, 0x021D1694))},
            {0x021d16a0, PatchElement("li r3, 1", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x028c23fc, 0x021d16a0))},
        };
    }

    bool BGMEcho::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(BGMEcho)
}
