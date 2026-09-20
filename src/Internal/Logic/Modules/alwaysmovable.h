//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
	class AlwaysMovableUpdate : public UpdateModule {
    VCLASS(AlwaysMovableUpdate, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };

	class AlwaysMovablePatch : public PatchModule {
    VCLASS(AlwaysMovablePatch, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        AlwaysMovablePatch();
    };

    class AlwaysMovableWrapper : public UpdateModule {
    VCLASS(AlwaysMovableWrapper, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
