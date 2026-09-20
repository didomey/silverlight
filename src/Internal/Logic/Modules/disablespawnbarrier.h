//
// Created by tv on 04.11.23.
//

#pragma once

#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class DisableSpawnBarrier : public UpdateModule {
    VCLASS(DisableSpawnBarrier, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
