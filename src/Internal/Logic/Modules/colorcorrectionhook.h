//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"
#include "Game/agl/pfx/ColorCorrection.h"

extern agl::pfx::ColorCorrection::ColorCorrection* colorCorrectionInstance;

namespace Modules {
    class ColorCorrectionHook : public PatchModule {
    VCLASS(ColorCorrectionHook, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        ColorCorrectionHook();
    };
}
