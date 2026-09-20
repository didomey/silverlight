#include "Game/Macros.h"
#include <glm/vec3.hpp>

namespace Cnet {
	namespace NetErrorScreen {
		#pragma pack(push, 1)
		struct NetErrorScreen {
			int32_t vtable;

			NetErrorScreen() {
				this->vtable = 0x10025e14;
			}
		};
		#pragma pack(pop)

		FUNCBIND(in, 0217e7bc, void(*)(NetErrorScreen* _this))
	}
}
