//
// Created by tv on 04.11.23.
//

#pragma once

#include "Internal/Logic/UpdateModule.h"


#include "Game/Player.h"

namespace Modules {
    class ChargeHoldUpdate : public UpdateModule {
    public:
    VCLASS(ChargeHoldUpdate, ESC({&UpdateModule::classInfo, nullptr}))

        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;

		Game::Player::Player* closestPlayer;
		float closestPlayerDist;
    };

	class ChargeHoldPatch : public PatchModule {
    VCLASS(ChargeHoldPatch, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        ChargeHoldPatch();
    };

    class ChargeHoldWrapper : public UpdateModule {
    public:
    VCLASS(ChargeHoldWrapper, ESC({&UpdateModule::classInfo, nullptr}))

        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
    };
}
