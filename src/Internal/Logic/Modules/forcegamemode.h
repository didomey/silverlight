//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/UpdateModule.h"
#include "Internal/Logic/modules.h"
#include "InputModule.h"

namespace Modules {
	class ForceGamemodeInput : public InputModule {
    VCLASS(ForceGamemodeInput, ESC({&InputModule::classInfo, nullptr}))
		void receivedEntry(const std::u16string &input) override;
		
		uint32_t gamemode;
    };

    class ForceGamemode : public PatchModule {
    VCLASS(ForceGamemode, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        ForceGamemode();
    };
}
