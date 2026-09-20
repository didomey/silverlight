//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/UpdateModule.h"
#include "Internal/Logic/modules.h"
#include "InputModule.h"

namespace Modules {
	class ChangeSkyboxInput : public InputModule {
    VCLASS(ChangeSkyboxInput, ESC({&InputModule::classInfo, nullptr}))
		void receivedEntry(const std::u16string &input) override;
		
		std::string skybox;
    };

    class ChangeSkybox : public PatchModule {
    VCLASS(ChangeSkybox, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

		std::string helpText() override;

        ChangeSkybox();
    };
}
