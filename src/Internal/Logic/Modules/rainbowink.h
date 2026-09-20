//
// Created by tv on 04.11.23.
//

#pragma once

#include<glm/vec3.hpp>
#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class RainbowInkUpdate : public UpdateModule {
    VCLASS(RainbowInkUpdate, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;

		float rainbowTimer = 0;
    };

	class RainbowInkPatch : public PatchModule {
    VCLASS(RainbowInkPatch, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        RainbowInkPatch();
    };

    class RainbowInkWrapper : public UpdateModule {
    VCLASS(RainbowInkWrapper, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
