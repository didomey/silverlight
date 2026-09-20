//
// Created by tv on 04.11.23.
//

#pragma once

#include<glm/vec3.hpp>
#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class StalkPlayer : public UpdateModule {
    VCLASS(StalkPlayer, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        void render(float deltaTime) override;

        bool isCheatModule() override;

        void update(float deltaTime) override;

        glm::vec3 m_lastPlayerPosition = {};

		int selectedPlayer;
    };
}
