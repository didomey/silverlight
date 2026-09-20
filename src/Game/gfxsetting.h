#include "Macros.h"

namespace Cmn {
	namespace GfxSetting {
		FUNCBINDUNK(020436A0, int(*)(uint32_t* _this, uint32_t *param_1, int32_t param_2));
		FUNCBIND(setAsSceneStart, 02043200, void(*)(uint32_t* _this, int32_t param_1))

		GVARBIND(sInstance, 101de170, uint32_t*)

	}
}
