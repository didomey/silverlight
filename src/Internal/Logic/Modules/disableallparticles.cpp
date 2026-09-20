#include"disableallparticles.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    DisableAllParticles::DisableAllParticles() {
        this->patch = {
                {0x02abdfe8, PatchElement("blr", "lwz r0, 0x58c(r3)")},
        };
    }

    bool DisableAllParticles::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DisableAllParticles)
}
