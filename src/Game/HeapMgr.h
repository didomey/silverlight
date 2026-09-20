#include "Game/Macros.h"

namespace sead {
	namespace HeapMgr {
		FUNCBIND(setCurrentHeap_, 028f2f80, int32_t(*)(int32_t* _this, int param_1))
		FUNCBIND(getCurrentHeap, 028f2e98, int32_t(*)(int32_t* _this))

		GVARBIND(sInstancePtr, 101e6af0, uint32_t*);
	}
}
