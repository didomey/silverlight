//
// Created by tv on 04.11.23.
//

#pragma once

#include<glm/vec3.hpp>
#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class FreecamUpdate : public UpdateModule {
    VCLASS(FreecamUpdate, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;

		glm::vec3 origPlayerPos = {};
		glm::vec3 playerCameraPos = {};
    };

    class FreecamPatch : public PatchModule {
    VCLASS(FreecamPatch, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        FreecamPatch();
    };

    class FreecamWrapper : public UpdateModule {
    VCLASS(FreecamWrapper, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
