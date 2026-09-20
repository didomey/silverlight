//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class PhotographModePatch : public PatchModule {
    VCLASS(PhotographModePatch, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        PhotographModePatch();
    };

	class PhotographModeUpdate : public UpdateModule {
    VCLASS(PhotographModeUpdate, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;

		bool requireRenderFocus() override;
    };

	class PhotographModeWrapper : public UpdateModule {
    VCLASS(PhotographModeWrapper, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
