//
// Created by tv on 04.11.23.
//

#pragma once

#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class ShowFPS : public UpdateModule {
    VCLASS(ShowFPS, ESC({&UpdateModule::classInfo, nullptr}))
    public:
		ShowFPS();

        void start() override;

        void stop() override;

        void render(float deltaTime) override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
