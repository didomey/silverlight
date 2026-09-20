#include <cstdint>
#include <array>
#include "Macros.h"

namespace Game {
	namespace PaintMgr {
		struct PaintMgr {
			std::array<char, 0x7cd80> unk1;
			uint32_t* m_unk1;
		};

		FUNCBIND(resetInk, 02447f48, void(*)(uint32_t* _this))

		GVARBIND(sInstance, 101e2948, PaintMgr *)
	}
}
