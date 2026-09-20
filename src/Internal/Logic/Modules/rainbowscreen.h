//
// Created by tv on 04.11.23.
//

#pragma once

#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class RainbowScreen : public UpdateModule {
    public:
    VCLASS(RainbowScreen, ESC({&UpdateModule::classInfo, nullptr}))

        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
