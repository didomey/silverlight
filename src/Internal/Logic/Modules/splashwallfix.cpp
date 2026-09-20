#include"splashwallfix.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    SplashWallFix::SplashWallFix() {
        this->patch = {
            {0x0269D114, PatchElement("li r5, 0", "clrlwi r5, r5, 24")},
        };
    }

    bool SplashWallFix::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(SplashWallFix)
}
