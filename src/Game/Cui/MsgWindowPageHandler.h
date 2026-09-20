#pragma once

#include "Game/Macros.h"
#include <glm/vec3.hpp>
#include "Game/Cui/MsgArg.h"

namespace Cui {
	namespace MsgWindowPageHandler {
		struct MsgWindowPageHandler {
			std::array<char, 0x34> unk1;
			bool buttonPressed;
		};

		ENSURE_OFFSET(MsgWindowPageHandler, buttonPressed, 0x34);

		FUNCBIND(isAbleIn, 0209bb54, bool(*)(MsgWindowPageHandler* _this))
		FUNCBIND(in, 0209bb68, void(*)(MsgWindowPageHandler* _this, Cui::MsgArg::MsgArg* msgArg))
	}
}
