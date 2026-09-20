//
// Created by tv on 04.11.23.
//

#pragma once

#include<glm/vec3.hpp>
#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class Scaffold : public UpdateModule {
	VCLASS(Scaffold, ESC({&UpdateModule::classInfo, nullptr}))

    public:
        void start() override;

        void stop() override;

        void update(float deltaTime) override;

		bool isCheatModule() override;
    };
}
