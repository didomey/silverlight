//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class JoinRankedThroughFriends : public PatchModule {
    VCLASS(JoinRankedThroughFriends, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;
		std::string helpText() override;

        JoinRankedThroughFriends();
    };
}
