//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/UpdateModule.h"
#include "Internal/Logic/modules.h"

namespace Modules {
    class NoclipEverywherePatch : public PatchModule {
    VCLASS(NoclipEverywherePatch, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        NoclipEverywherePatch();

		bool antiDeathZoneModulePreviouslyEnabled;
    };

	class NoclipEverywhereUpdate : public UpdateModule {
    VCLASS(NoclipEverywhereUpdate, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;

		bool antiDeathZoneModulePreviouslyEnabled;
    };

    class NoclipEverywhereWrapper : public UpdateModule {
    VCLASS(NoclipEverywhereWrapper, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
