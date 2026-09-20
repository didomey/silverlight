//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class HideLowInkWarning : public PatchModule {
    VCLASS(HideLowInkWarning, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        HideLowInkWarning();
    };
}
