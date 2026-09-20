//
// Created by tv on 04.11.23.
//

#pragma once

#include<glm/vec3.hpp>
#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class ShowCopyrightText : public UpdateModule {
    VCLASS(ShowCopyrightText, ESC({&UpdateModule::classInfo, nullptr}))
    public:
		ShowCopyrightText();

        void start() override;

        void stop() override;

        void render(float deltaTime) override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
