//
// Created by tv on 04.11.23.
//

#pragma once

#include "Internal/Logic/UpdateModule.h"


#include "Game/Player.h"

namespace Modules {
    class AimBotUpdate : public UpdateModule {
    public:
    VCLASS(AimBotUpdate, ESC({&UpdateModule::classInfo, nullptr}))

        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;

        void render(float deltaTime) override;

		Game::Player::Player* closestPlayer;
		float closestPlayerDist;
    };

	class AimBotPatch : public PatchModule {
    VCLASS(AimBotPatch, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        AimBotPatch();
    };

    class AimBotWrapper : public UpdateModule {
    public:
    VCLASS(AimBotWrapper, ESC({&UpdateModule::classInfo, nullptr}))

        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
