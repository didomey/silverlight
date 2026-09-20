//
// Created by tv on 04.11.23.
//
#include"alwaysmovable.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include "Internal/Logic/modules.h"
#include "Game/player.h"
#include "Game/CameraUnk.h"
#include "Internal/silverlight.h"
#include "Game/SceneMgr.h"
#include "Game/Controller.h"
#include "Game/pausemenu.h"

bool repl_isInState_NoControl(uint32_t* _this, int param_1) {
	return false;
}

bool repl_isHoldingSpecial_SuperLaser(uint32_t* _this, int param_1) {
	return false;
}

bool repl_isHoldingSpecial_Inkstrike(uint32_t* _this) {
	return false;
}

namespace Modules {
	void AlwaysMovableUpdate::start() {
    }

    void AlwaysMovableUpdate::stop() {
	}

    void AlwaysMovableUpdate::update(float deltaTime) {
		if (!Lp::Sys::SceneMgr::sceneHasLoaded(Lp::Sys::SceneMgr::sInstance)) return;
		if (!CameraMgr::sInstance) return;
		if (!CameraMgr::sInstance->camera1) return;
    }

    bool AlwaysMovableUpdate::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AlwaysMovableUpdate)

    AlwaysMovablePatch::AlwaysMovablePatch() {
        this->patch = {
			{ 0x026331d8, PatchElement(
				DynamicBranchReplacementSingle(BranchType::Branch, (void *) repl_isInState_NoControl, 0x026331d8),
				"mflr r0"
			)},
			{ 0x0262d6a8, PatchElement(
				DynamicBranchReplacementSingle(BranchType::Branch, (void *) repl_isHoldingSpecial_SuperLaser, 0x0262d6a8),
				"mflr r0"
			)},
			{ 0x0262d768, PatchElement(
				DynamicBranchReplacementSingle(BranchType::Branch, (void *) repl_isHoldingSpecial_Inkstrike, 0x0262d768),
				"mflr r0"
			)}
		};
    }

    bool AlwaysMovablePatch::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AlwaysMovablePatch)

    void AlwaysMovableWrapper::start() {
		AlwaysMovableUpdate *alwaysMovableUpdateModule = silverlightInstance->m_moduleStates.getModule<AlwaysMovableUpdate>();
		AlwaysMovablePatch *alwaysMovablePatchModule = silverlightInstance->m_moduleStates.getModule<AlwaysMovablePatch>();

		alwaysMovableUpdateModule->enable();
		alwaysMovablePatchModule->enablePatch();
    }

    void AlwaysMovableWrapper::stop() {
		AlwaysMovableUpdate *alwaysMovableUpdateModule = silverlightInstance->m_moduleStates.getModule<AlwaysMovableUpdate>();
		AlwaysMovablePatch *alwaysMovablePatchModule = silverlightInstance->m_moduleStates.getModule<AlwaysMovablePatch>();

		alwaysMovableUpdateModule->disable();
		alwaysMovablePatchModule->disablePatch();
	}

    void AlwaysMovableWrapper::update(float deltaTime) {
    }

    bool AlwaysMovableWrapper::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AlwaysMovableWrapper)
}
