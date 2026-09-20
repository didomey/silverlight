//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class DisableShotGuide : public PatchModule {
    VCLASS(DisableShotGuide, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        DisableShotGuide();
    };
}
