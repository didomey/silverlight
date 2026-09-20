#include"improvedwallpaint.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>
#include "Game/Player.h"

float repl_FUN_0263b304(Game::Player::Player* _this) {
	return 1.0;
}

namespace Modules {
    ImprovedWallPaint::ImprovedWallPaint() {
        this->patch = {
            {0x02646054, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_FUN_0263b304, 0x02646054), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x0263b304, 0x02646054))},
        };
    }

    bool ImprovedWallPaint::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(ImprovedWallPaint)
}
