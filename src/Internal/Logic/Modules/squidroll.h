#pragma once

#include "Internal/Logic/UpdateModule.h"


#include "Game/Player.h"

#include <glm/vec2.hpp>

enum class SquidRollState {
	Inactive, StickInputCheck, JumpInputCheck, Upward, Downward
};

#define INPUT_BUF_SIZE 15
#define JUMP_FRM_WINDOW 10

#define INITIAL_ACCEL 2.0
#define UPWARD_ACCEL 0.12
#define DOWNWARD_ACCEL 0.19
#define MAX_DOWNWARD_ACCEL -1.85

#define MIN_STICK_DIST 0.55

#define EXTRA_ARMOR_FRM 10

namespace Modules {
    class SquidRoll : public UpdateModule {
    public:
    VCLASS(SquidRoll, ESC({&UpdateModule::classInfo, nullptr}))

        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;

        void render(float deltaTime) override;

		void stateInactive();
		void stateStickInputCheck();
		void stateJumpInputCheck();
		void stateUpward();
		void stateDownward();
		void stateArmorCheck();

		void stateMoveHorizontal();

		SquidRollState state;

		int32_t armorStateBeforeInit;

		glm::vec2 stickPos;
		glm::vec3 position;
		glm::vec3 initialActivePlayerPosition;

		glm::vec2 stickPosBuf[INPUT_BUF_SIZE];
		uint32_t bufIdx = 0;

		float verticalAccel;

		uint16_t remainingPossibleJumpFrm = 10;

		uint32_t remainingInvincibilityFrm;
    };

	class DisableJumpEffectHook : public PatchModule {
    VCLASS(DisableJumpEffectHook, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        DisableJumpEffectHook();
    };
}
