//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class NoHash : public PatchModule {
    VCLASS(NoHash, ESC({&PatchModule::classInfo, nullptr}))
    public:
        NoHash();

        bool isCheatModule() override;
    };
}
