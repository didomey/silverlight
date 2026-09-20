#include "Game/GameROMMgr.h"
#include "Game/DebugInfo.h"
#include "switchscene.h"

namespace Modules {
	void enterShowfloor() {
		Game::DebugInfo::sInstance->romType = "ShowFloor";
		Lp::Sys::GameROMMgr::sInstance->romType = 1;
		//*Lp::Sys::GameROMMgr::sInstance = Lp::Sys::GameROMMgr::_GameROMMgr(Lp::Sys::GameROMMgr::sInstance);
		//Lp::Sys::GameROMMgr::createGameROMMgr(Lp::Sys::GameROMMgr::sInstance);
		switchScene(22);
	}
}
