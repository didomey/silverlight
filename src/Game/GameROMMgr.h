#include "Game/Macros.h"
#include <array>
#include <glm/vec3.hpp>

namespace Lp {
	namespace Sys {
		namespace GameROMMgr {
			#pragma pack(push, 1)
			struct GameROMMgr {
				std::array<char, 0x10> unk1;
				uint32_t romType;
			};
			#pragma pack(pop)

			FUNCBIND(createGameROMMgr, 0202edc4, int32_t(*)(Lp::Sys::GameROMMgr::GameROMMgr* _this))
			FUNCBIND(_GameROMMgr, 0202eb74, Lp::Sys::GameROMMgr::GameROMMgr(*)(Lp::Sys::GameROMMgr::GameROMMgr* _this))

			GVARBIND(sInstance, 101dd328, GameROMMgr *)
		}
	}
}
