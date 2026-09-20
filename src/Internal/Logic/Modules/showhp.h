//
// Created by tv on 04.11.23.
//

#pragma once

#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class ShowHP : public UpdateModule {
    VCLASS(ShowHP, ESC({&UpdateModule::classInfo, nullptr}))
    public:
		ShowHP();

        void start() override;

        void stop() override;

        void render(float deltaTime) override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
