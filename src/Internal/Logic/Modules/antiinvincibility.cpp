#include"antiinvincibility.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    AntiInvincibility::AntiInvincibility() {
        this->patch = {
                {0x02645F14, PatchElement("li r3, 0", "clrlwi r3, r30, 24")},
                {0x0264FA38, PatchElement("li r3, 0", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x0262d540, 0x0264fa38))},
                {0x026362C4, PatchElement("li r3, 0", "clrlwi r3, r5, 24")},
                {0x0267B938, PatchElement("li r3, 0", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02645de0, 0x0264fa38))},
                {0x0267b8fc, PatchElement("li r3, 1", "lwz r0, 0x50(r6)")},
        };
    }

    bool AntiInvincibility::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(AntiInvincibility)
}
