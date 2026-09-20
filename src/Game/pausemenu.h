#include "Game/Macros.h"

namespace PauseMenu {
	FUNCBIND(isPauseMenuEnabled, 0219894c, uint32_t(*)(void))
	
	namespace Unk {
		FUNCBIND(finishedOpeningMenu, 02198d18, uint32_t(*)(uint32_t* param_1, uint32_t* param_2))

		GVARBIND(sInstance, 101e083c, uint32_t*);
	}
}
