//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class SilverlightMatchmaking : public PatchModule {
    VCLASS(SilverlightMatchmaking, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;
		std::vector<const char*> incompatibleModules() override;

        SilverlightMatchmaking();
    };
}
