//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

struct PlayerNetState {
	bool isRevived;
	std::chrono::_V2::system_clock::time_point lastReviveTime;

	bool dokanWarpActive;
	std::chrono::_V2::system_clock::time_point lastDokanWarpUpdateTime;
};

extern PlayerNetState playerNetStates[8];
extern PlayerNetState prevPlayerNetStates[8];

namespace Modules {
    class PlayerEventHook : public PatchModule {
    VCLASS(PlayerEventHook, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        PlayerEventHook();
    };
}
