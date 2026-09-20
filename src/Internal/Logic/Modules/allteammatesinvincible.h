//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class AllTeammatesInvinciblePatch : public PatchModule {
    public:
    VCLASS(AllTeammatesInvinciblePatch, ESC({&PatchModule::classInfo, nullptr}))

        AllTeammatesInvinciblePatch();

        bool isCheatModule() override;
    };
}
