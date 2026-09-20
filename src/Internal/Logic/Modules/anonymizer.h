//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class AnonymizerPatch : public PatchModule {
    VCLASS(AnonymizerPatch, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        AnonymizerPatch();
    };

    class AnonymizerUpdate : public UpdateModule {
    VCLASS(AnonymizerUpdate, ESC({&UpdateModule::classInfo, nullptr}))

    public:
        void start() override;

        void stop() override;

        void update(float deltaTime) override;

        std::string m_oldname;

        bool isCheatModule() override;
    };

    class AnonymizerWrapper : public UpdateModule {
    VCLASS(AnonymizerWrapper, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
