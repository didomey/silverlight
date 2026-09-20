#pragma once

#include "Game/Macros.h"
#include "BulletCloneEvent.h"

namespace Game {
	namespace PacketBulletCloneEvent {
		#pragma pack(push, 1)
		struct PacketBulletCloneEvent {
		};
		#pragma pack(pop)

		FUNCBIND(expand, 0266c270, void(*)(Game::PacketBulletCloneEvent::PacketBulletCloneEvent* _this, Game::BulletCloneEvent::BulletCloneEvent* cloneEvent))
	}
}
