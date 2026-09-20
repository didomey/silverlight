//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
	void skipIntro();

	void endGame();

    class EndGameHook : public PatchModule {
    VCLASS(EndGameHook, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        EndGameHook();
    };
}
