//
// Created by tv on 04.11.23.
//

#pragma once

#include "Internal/Logic/UpdateModule.h"


#include "Game/Player.h"

namespace Modules {
    class CPSMode : public UpdateModule {
    public:
    VCLASS(CPSMode, ESC({&UpdateModule::classInfo, nullptr}))

        void start() override;

        void stop() override;

        bool isCheatModule() override;

		std::string helpText() override;

    public:
        void update(float deltaTime) override;

        void render(float deltaTime) override;

		Game::Player::Player* closestPlayer;
		float closestPlayerDist;
    };
}
