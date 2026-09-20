//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class PauseMenuAlwaysUsable : public PatchModule {
    VCLASS(PauseMenuAlwaysUsable, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        PauseMenuAlwaysUsable();
    };
}
