#pragma once

namespace Game {
	namespace VictoryGoal {
		enum class TowerState {
			ControlledByAlpha,
			ControlledByBravo,
			Uncontrolled,
		};

		struct VictoryGoal {
			 TowerState getTowerState();
		};
	}
}
