//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"
#include "InputModule.h"

namespace Modules {
	class TransitionInput : public InputModule {
    VCLASS(InTransitionInput, ESC({&InputModule::classInfo, nullptr}))
		void receivedEntry(const std::u16string &input) override;
		
		uint32_t transitionId = 0;
    };

    class CustomizeTransition : public PatchModule {
    VCLASS(CustomizeTransition, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        CustomizeTransition();
    };
}
