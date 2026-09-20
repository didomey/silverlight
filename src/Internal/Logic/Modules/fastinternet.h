//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"

namespace Modules {
    class FastInternetPatch : public PatchModule {
    VCLASS(FastInternetPatch, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        FastInternetPatch();

		bool m_enabled = true;
    };

    class FastInternetWrapper : public UpdateModule {
    VCLASS(FastInternetWrapper, ESC({&UpdateModule::classInfo, nullptr}))
    public:
		FastInternetWrapper();

        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;

		bool m_enabled = true;
    };
}
