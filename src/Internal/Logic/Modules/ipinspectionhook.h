//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class IPInspectionHook : public PatchModule {
    VCLASS(IPInspectionHook, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        void onEnable() override;
        void onDisable() override;

        IPInspectionHook();
    };
}
