#include "Game/Macros.h"

namespace Lp {
	namespace Sys {
		namespace SceneMgr {
			FUNCBIND(sceneHasLoaded, 028a02f0, bool(*)(uint32_t* param_1))
			FUNCBIND(getCurSceneId, 028c67ec, int32_t(*)(void))

			GVARBIND(sInstance, 101e6770, uint32_t*);


		}
	}
}
