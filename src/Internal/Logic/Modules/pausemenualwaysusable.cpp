//
// Created by tv on 04.11.23.
//
#include"pausemenualwaysusable.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include "Game/pausemenu.h"
#include "Game/SceneMgr.h"

bool repl_isPauseMenuEnabled() {
	int curSceneId = Lp::Sys::SceneMgr::getCurSceneId();
	if (curSceneId == 1 || curSceneId == 2 || curSceneId == 0xf || curSceneId == 3) {
		return false;
	}
	return true;
}

namespace Modules {
    PauseMenuAlwaysUsable::PauseMenuAlwaysUsable() {
        this->patch = {
            {0x02198f78, PatchElement(
					DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) repl_isPauseMenuEnabled, 0x02198f78),
					DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) PauseMenu::isPauseMenuEnabled, 0x02198f78)
					)},
        };
		this->enablePatch();
    }

    bool PauseMenuAlwaysUsable::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(PauseMenuAlwaysUsable)
}
