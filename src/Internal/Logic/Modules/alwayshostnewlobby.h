//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class AlwaysHostNewLobby : public PatchModule {
    VCLASS(AlwaysHostNewLobby, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        AlwaysHostNewLobby();
    };
}
