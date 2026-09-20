#pragma once

#include "Game/Macros.h"
#include <glm/vec3.hpp>
#include "Game/sead/SafeString.h"
#include "Game/Cui/MsgWindowPageHandler.h"
#include <array>

namespace Cui {
	namespace SystemPageMgr {
		struct SystemPageMgr {
			std::array<char, 0x60> unk1;
			Cui::MsgWindowPageHandler::MsgWindowPageHandler* msgWindowPageHandler;

			Cui::MsgWindowPageHandler::MsgWindowPageHandler* getWindowPageHandler();
		};

		ENSURE_OFFSET(SystemPageMgr, msgWindowPageHandler, 0x60);

		GVARBIND(sInstance, 101dfaec, SystemPageMgr*)
	}
}
