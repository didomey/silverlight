//
// Created by tv on 04.11.23.
//

#pragma once

#include<glm/vec3.hpp>
#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class ZeroPaint : public UpdateModule {
    VCLASS(ZeroPaint, ESC({&UpdateModule::classInfo, nullptr}))
    public:
		ZeroPaint();

        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
