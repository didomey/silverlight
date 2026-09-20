//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class FreezeTimer : public PatchModule {
    VCLASS(FreezeTimer, ESC({&PatchModule::classInfo, nullptr}))
    public:

        bool isCheatModule() override;

        FreezeTimer();
    };
}
