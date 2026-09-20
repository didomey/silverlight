//
// Created by tv on 04.11.23.
//
#include"futurefly.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

#include "time.h"

namespace Modules {
    MatchTime::MatchTime() {
        this->patch = {
                {0x0274c290, PatchElement("li r5, " + )}
        };
        this->additionalOpt = {"1 Minute", "5 Minutes"};
    }

    REGISTERVCLASS(MatchTime)
}
