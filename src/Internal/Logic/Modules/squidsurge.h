#pragma once

#include "Internal/Logic/UpdateModule.h"


#include "Game/Player.h"

#include <glm/vec2.hpp>

enum class SquidSurgePhase {
	Inactive, InactiveReady, Upward, Downward
};

namespace Modules {
    class SquidSurge : public UpdateModule {
    public:
    VCLASS(SquidSurge, ESC({&UpdateModule::classInfo, nullptr}))

        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;

        void render(float deltaTime) override;

		void stateInactive();
		void stateInactiveReady();
		void stateUpward();
		void stateDownward();

		float verticalAccel;

		SquidSurgePhase phase;

		glm::vec2 dir;
		glm::vec3 position;
		glm::vec3 initialActivePlayerPosition;
    };
}
