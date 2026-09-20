//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class NoAutoCameraMovement : public PatchModule {
    VCLASS(NoAutoCameraMovement, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        NoAutoCameraMovement();
    };
}
