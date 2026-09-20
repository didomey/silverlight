//
// Created by tv on 04.11.23.
//
#include"noclipeverywhere.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>
#include "antideathzone.h"
#include "Internal/silverlight.h"

bool repl_isPlayerCollide(MainMgr* _this, int param_1) {
	return !_this->m_isLocalPlayer;
}

namespace Modules {
    NoclipEverywherePatch::NoclipEverywherePatch() {
        this->patch = {
			{0x026314c0, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) repl_isPlayerCollide, 0x026314c0), "mflr r0")},
        };
    }

    bool NoclipEverywherePatch::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(NoclipEverywherePatch)

    void NoclipEverywhereUpdate::start() {
		AntiDeathZone *antiDeathZoneModule = silverlightInstance->m_moduleStates.getModule<AntiDeathZone>();
		this->antiDeathZoneModulePreviouslyEnabled = antiDeathZoneModule->m_enabled;
    }

    void NoclipEverywhereUpdate::stop() {
		AntiDeathZone *antiDeathZoneModule = silverlightInstance->m_moduleStates.getModule<AntiDeathZone>();
		antiDeathZoneModule->m_enabled = this->antiDeathZoneModulePreviouslyEnabled;
		antiDeathZoneModule->apply();
    }

    void NoclipEverywhereUpdate::update(float deltaTime) {
		AntiDeathZone *antiDeathZoneModule = silverlightInstance->m_moduleStates.getModule<AntiDeathZone>();
		antiDeathZoneModule->enablePatch();
    }

    bool NoclipEverywhereUpdate::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(NoclipEverywhereUpdate)

    void NoclipEverywhereWrapper::start() {
		NoclipEverywhereUpdate *noclipEverywhereUpdateModule = silverlightInstance->m_moduleStates.getModule<NoclipEverywhereUpdate>();
		NoclipEverywherePatch *noclipEverywherePatchModule = silverlightInstance->m_moduleStates.getModule<NoclipEverywherePatch>();

		noclipEverywhereUpdateModule->m_enabled = true;
		noclipEverywherePatchModule->enablePatch();
    }

    void NoclipEverywhereWrapper::stop() {
		NoclipEverywhereUpdate *noclipEverywhereUpdateModule = silverlightInstance->m_moduleStates.getModule<NoclipEverywhereUpdate>();
		NoclipEverywherePatch *noclipEverywherePatchModule = silverlightInstance->m_moduleStates.getModule<NoclipEverywherePatch>();

		noclipEverywhereUpdateModule->m_enabled = false;
		noclipEverywherePatchModule->disablePatch();
	}

    void NoclipEverywhereWrapper::update(float deltaTime) {
    }

    bool NoclipEverywhereWrapper::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(NoclipEverywhereWrapper)
}
