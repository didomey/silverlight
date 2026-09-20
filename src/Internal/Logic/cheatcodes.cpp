/*
#include "Internal/silverlight.h"
#include "Internal/Logic/Modules/showfloor.h"
#include "Shared/Cafe/vpad.h"
#include "Game/SceneMgr.h"

namespace Controller {
	void cheatCodesCheck() {
		int curSceneId = Lp::Sys::SceneMgr::getCurSceneId();

		CAFEINFO(std::to_string(curSceneId));

		static Inputs lastHeld = {};

        VPADStatus status = {};
        VPADReadError err;

        VPADRead(VPAD_CHAN_0, &status, 1, &err);

        Inputs *held = (Inputs *) &status.hold;

        if (curSceneId == 0 && held->ButtonL) {
			Modules::Showfloor *showfloorPatchModule = silverlightInstance->m_moduleStates.getModule<Modules::Showfloor>();						
			showfloorPatchModule->enablePatch();
        }
	}
}
*/
