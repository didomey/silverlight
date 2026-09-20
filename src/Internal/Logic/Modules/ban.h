//
// Created by tv on 01.12.23.
//

#pragma once

#include<Internal/Logic/modules.h>

namespace Modules {

    class Ban : UpdateModule {
    VCLASS(Ban, ESC({&UpdateModule::classInfo, nullptr}))
    private:
        void start() override;

        bool isCheatModule() override;

        void stop() override;

        void update(float deltaTime) override;
    };

} // Modules
