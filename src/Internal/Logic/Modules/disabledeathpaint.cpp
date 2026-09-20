#include"disabledeathpaint.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    DisableDeathPaint::DisableDeathPaint() {
        this->patch = {
                {0x0264F804, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x022067f4, 0x0264F804))},
        };
    }

    bool DisableDeathPaint::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(DisableDeathPaint)
}
