//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class MissionOnlineCrashFixes : public PatchModule {
    VCLASS(MissionOnlineCrashFixes, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        MissionOnlineCrashFixes();
    };
}
