#include "Game/Cui/SystemPageMgr.h"
#include "Game/Cui/MsgWindowPageHandler.h"

namespace Cui {
	MsgWindowPageHandler::MsgWindowPageHandler* SystemPageMgr::SystemPageMgr::getWindowPageHandler() {
		return sInstance->msgWindowPageHandler;
	}
}
