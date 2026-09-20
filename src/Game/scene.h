#include "Game/Macros.h"

namespace SceneUtil {
	FUNCBIND(getSceneName, 028c6738, char*(*)(void))
	FUNCBIND(handleSceneTransition, 020826d8, void(*)(uint32_t* param_1, uint32_t id))
}

struct TransitionInfo {
	std::string name;
	uint32_t id;
};

inline std::array<TransitionInfo, 8> transitions = {
	{
		{"Amiibo", 0},
		{"Normal Fade", 1},
		{"Circle Fade", 2},
		{"Standard", 3},
		{"Cleaner", 4},
		{"Cleaner 2", 5},
		{"Amiibo 2", 6},
		{"Normal Fade 2", 7},
	}
};
