//
// Created by tv on 04.11.23.
//
#include"infiniteink.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    InfiniteInk::InfiniteInk() {
        this->patch = {{0x0268A228, PatchElement("nop", "stfs f13, 0(r26)")}};
    }

    bool InfiniteInk::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(InfiniteInk)
}
