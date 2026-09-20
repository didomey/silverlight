//
// Created by tv on 04.11.23.
//
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

#include "nohash.h"

namespace Modules {
    NoHash::NoHash() {
        this->patch = {
                {0x027B3048, PatchElement("lis r4, 0x7AAF", "lwz r4, 0(r30)")},
                {0x027B304C, PatchElement("ori r4, r4,0x4CD4", "add r4, r4, r3")},
                {0x027B3050, PatchElement("stwu r4, 0(r30)", "stw r4, 0(r30)")}
        };
        this->enablePatch();
    }

    bool NoHash::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(NoHash)
}
