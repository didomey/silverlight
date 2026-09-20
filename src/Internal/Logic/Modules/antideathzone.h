//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class AntiDeathZone : public PatchModule {
    public:
    VCLASS(AntiDeathZone, ESC({&PatchModule::classInfo, nullptr}))

        AntiDeathZone();

        bool isCheatModule() override;
    };
}
