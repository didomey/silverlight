#pragma once

#include "Game/Macros.h"
#include <glm/vec3.hpp>
#include "Game/Cui/MsgWindowPageHandler.h"

namespace Cmn {
	namespace DayChangeChecker {
		#pragma pack(push, 1)
		struct DayChangeChecker {
			std::array<char, 0x168> unk1;
			uint32_t buttonPressed;

			std::array<char, 0x2c> unk2;
			Cui::MsgWindowPageHandler::MsgWindowPageHandler* msgWindowPageHandler;
		};
		#pragma pack(pop)

		ENSURE_OFFSET(DayChangeChecker, buttonPressed, 0x168);
		ENSURE_OFFSET(DayChangeChecker, msgWindowPageHandler, 0x198);

		GVARBIND(sInstance, 101e09cc, DayChangeChecker*)
	}
}
