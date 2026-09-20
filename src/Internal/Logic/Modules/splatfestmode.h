//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"
#include "Internal/Logic/UpdateModule.h"
#include "Internal/silverlight.h"

namespace Modules {
    class SplatfestModePatch : public PatchModule {
    VCLASS(SplatfestModePatch, ESC({&PatchModule::classInfo, nullptr}))
    public:

        bool isCheatModule() override;

        SplatfestModePatch();
    };

	class SplatfestModeUpdate : public UpdateModule {
    VCLASS(SplatfestModeUpdate, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };

	class SplatfestModeWrapper : public UpdateModule {
    VCLASS(SplatfestModeWrapper, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
