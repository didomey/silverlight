#pragma once

#include "Game/Macros.h"
#include <glm/vec3.hpp>
#include "Game/sead/SafeString.h"
#include <array>

namespace Cui {
	namespace MsgArg {
		#pragma pack(push, 1)
		struct MsgArg {
			int32_t success;
			std::array<char, 0x47c> unk;
		};
		#pragma pack(pop)

		FUNCBIND(ctor, 0209b0dc, void(*)(MsgArg* _this))
		FUNCBIND(onSettingMsgWinArg, 0209b39c, void(*)(MsgArg* _this, sead::SafeString::SafeString* msgType))
	}
}
