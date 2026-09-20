//
// Created by tv on 04.11.23.
//
#include"colorcorrectionhook.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>
#include "Game/agl/pfx/ColorCorrection.h"

agl::pfx::ColorCorrection::ColorCorrection* colorCorrectionInstance = nullptr;

void repl_ColorCorrection(agl::pfx::ColorCorrection::ColorCorrection* _this) {
	colorCorrectionInstance = _this;
	agl::pfx::ColorCorrection::ColorCorrectionCtor(_this);
}

namespace Modules {
    ColorCorrectionHook::ColorCorrectionHook() {
        this->patch = {
            {0x029e3f38, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_ColorCorrection, 0x029e3f38), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02a08a60, 0x029e3f38))},
            {0x02a177d0, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_ColorCorrection, 0x02a177d0), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02a08a60, 0x02a177d0))},
            {0x02a9bf84, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_ColorCorrection, 0x02a9bf84), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02a08a60, 0x02a9bf84))},
        };
        this->enablePatch();
    }

    bool ColorCorrectionHook::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(ColorCorrectionHook)
}
