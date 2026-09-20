#include"emote.h"
#include "Game/gfxsetting.h"
#include <stdint.h>
#include "Shared/colorconvert.h"
#include <glm/vec4.hpp>
#include "Internal/silverlight.h"
#include "Game/PlayerInkAction.h"
#include "Game/MainMgr.h"
#include "Game/PlayerAnimCtrlSet.h"

static int32_t emoteAnimID = 262;
static int32_t endAnimID = 132;

namespace Modules {
    void EmoteUpdate::start() {
		this->frm = 0;
		Game::PlayerMotion::startEventAnim(Game::PlayerMgr::sInstance->m_playerMotion, &emoteAnimID, 0.0, 1.0);
    }

    void EmoteUpdate::stop() {
		Game::PlayerMotion::changeBlend(Game::PlayerMgr::sInstance->m_playerMotion, &endAnimID, 117, 0);
	}

    void EmoteUpdate::update(float deltaTime) {
		if (this->frm > 60 * 4) {
			EmoteWrapper *emoteWrapperModule = silverlightInstance->m_moduleStates.getModule<EmoteWrapper>();
			emoteWrapperModule->disable();
		} else {
			this->frm++;
		}
	}

    bool EmoteUpdate::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(EmoteUpdate)
	
    EmotePatch::EmotePatch() {
        this->patch = {
			{0x026c4684, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::PlayerMotion::changeBlend, 0x026c4684))},
			{0x026c12e4, PatchElement("blr", "stwu r1, -0x88(r1)")},
			{0x026331d8, PatchElement("li r3, 1", "mflr r0")},
			{0x026331dc, PatchElement("blr", "stwu r1, -0x10(r1)")}
        };
    }

	void EmotePatch::onEnable() {
	}

	void EmotePatch::onDisable() {
	}

    bool EmotePatch::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(EmotePatch)

    void EmoteWrapper::start() {
		EmoteUpdate *emoteUpdateModule = silverlightInstance->m_moduleStates.getModule<EmoteUpdate>();
		EmotePatch *emotePatchModule = silverlightInstance->m_moduleStates.getModule<EmotePatch>();

		emotePatchModule->enablePatch();
		emoteUpdateModule->enable();
    }

    void EmoteWrapper::stop() {
		EmoteUpdate *emoteUpdateModule = silverlightInstance->m_moduleStates.getModule<EmoteUpdate>();
		EmotePatch *emotePatchModule = silverlightInstance->m_moduleStates.getModule<EmotePatch>();

		emotePatchModule->disablePatch();
		emoteUpdateModule->disable();
	}

    void EmoteWrapper::update(float deltaTime) {
    }

    bool EmoteWrapper::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(EmoteWrapper)
}
