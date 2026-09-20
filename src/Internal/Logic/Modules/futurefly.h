//
// Created by tv on 04.11.23.
//

#pragma once

#include<glm/vec3.hpp>
#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class FutureFly : public UpdateModule {
    VCLASS(FutureFly, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;


        glm::vec3 m_lastPlayerPosition = {};

        bool noclipEverywhereUpdateModulePreviouslyEnabled;
        bool noclipEverywherePatchModulePreviouslyEnabled;
    };
}
