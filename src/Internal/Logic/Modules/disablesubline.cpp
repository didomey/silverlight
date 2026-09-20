#include"disablesubline.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    DisableSubLine::DisableSubLine() {
        this->patch = {
                {0x0268746c, PatchElement("blr", "mflr r0")},
        };
    }

    bool DisableSubLine::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DisableSubLine)
}
