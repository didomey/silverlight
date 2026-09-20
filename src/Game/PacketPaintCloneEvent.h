#pragma once

#include "Game/Macros.h"
#include "PaintCloneEvent.h"

namespace Game {
	namespace PacketPaintCloneEvent {
		#pragma pack(push, 1)
		struct PacketPaintCloneEvent {
		};
		#pragma pack(pop)

		FUNCBIND(expand, 0266b978, void(*)(Game::PacketPaintCloneEvent::PacketPaintCloneEvent* _this, Game::PaintCloneEvent::PaintCloneEvent* cloneEvent))
	}
}
