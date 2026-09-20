//
// Created by tv on 04.11.23.
//

#pragma once

#include<glm/vec3.hpp>
#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class BHop : public UpdateModule {
    VCLASS(BHop, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        bool isCheatModule() override;

    public:
        void stop() override;

        void update(float deltaTime) override;
    };
}
