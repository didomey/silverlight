#include "Macros.h"
#include <array>

namespace Game {
	namespace DebugInfo {
		#pragma pack(push, 1)
		struct DebugInfo {
			std::array<char, 0x10> unk;
			const char* romType;
		};
		#pragma pack(pop)

		GVARBIND(sInstance, 101e6748, DebugInfo *)
	}
}
