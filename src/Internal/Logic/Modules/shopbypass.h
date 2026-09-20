//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class ShopBypass : public PatchModule {
    VCLASS(ShopBypass, ESC({&PatchModule::classInfo, nullptr}))
    public:

        bool isCheatModule() override;

        ShopBypass();
    };
}
