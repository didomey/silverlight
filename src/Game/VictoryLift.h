#pragma once

#include "Game/Macros.h"
#include <glm/vec3.hpp>

namespace Game {
	namespace VictoryLift {
		enum class TowerState {
            ControlledByAlpha,
            ControlledByBravo,
            Uncontrolled,
        };

		struct VictoryLift {
			static TowerState getTowerState();
		};

		FUNCBIND(isTowerMove, 025ecb98, bool(*)(void))
	}
}
