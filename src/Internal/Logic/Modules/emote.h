//
// Created by tv on 04.11.23.
//

#pragma once

#include<glm/vec3.hpp>
#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class EmoteUpdate : public UpdateModule {
    VCLASS(EmoteUpdate, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;

		int32_t frm;
    };

	class EmotePatch : public PatchModule {
    VCLASS(EmotePatch, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

		void onEnable() override;
		void onDisable() override;

        EmotePatch();
    };

    class EmoteWrapper : public UpdateModule {
    VCLASS(EmoteWrapper, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
