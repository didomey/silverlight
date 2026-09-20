//
// Created by tv on 04.11.23.
//

#pragma once

#include<glm/vec3.hpp>
#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class ShowPBPassword : public UpdateModule {
    VCLASS(ShowPBPassword, ESC({&UpdateModule::classInfo, nullptr}))
    public:
		ShowPBPassword();

        void start() override;

        void stop() override;

        void render(float deltaTime) override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
