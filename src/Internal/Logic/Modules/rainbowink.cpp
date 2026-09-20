#include"rainbowink.h"
#include "Game/gfxsetting.h"
#include <stdint.h>
#include "Shared/colorconvert.h"
#include <glm/vec4.hpp>
#include "Internal/silverlight.h"

FUNCBIND(calcInkColor, 02043de8, glm::vec4*(*)(int32_t param_1, uint32_t *param_2, uint32_t param_3, int32_t param_4))

static glm::vec4 color = { 1.0, 1.0, 1.0, 1.0 };

glm::vec4* repl_calcInkColor(int32_t param_1, uint32_t *param_2, uint32_t param_3, int32_t param_4) {
	return &color;
}

/*
static glm::vec4 color2 = { 1.0, 1.0, 1.0, 1.0};

glm::vec4* repl_calcInkColor_2(int32_t param_1, uint32_t *param_2, uint32_t param_3, int32_t param_4) {
	return &color2;
}
*/

namespace Modules {
    void RainbowInkUpdate::start() {
    }

    void RainbowInkUpdate::stop() {
	}

    void RainbowInkUpdate::update(float deltaTime) {
		float colorOffset = 0;

		this->rainbowTimer += 0.3333 / 80;

    	if (this->rainbowTimer > 1)
        	this->rainbowTimer -= 1;

		float colorHue = this->rainbowTimer + colorOffset;
        while (colorHue > 1)
            colorHue -= 1;

		auto calcColor = hsva2rgba({colorHue, 1, 1, 1});

		color = calcColor;

		Cmn::GfxSetting::FUN_020436A0(Cmn::GfxSetting::sInstance, (uint32_t*)(*(uint32_t*)0x101dd330 + 0x2e0), 0);
		Cmn::GfxSetting::setAsSceneStart(Cmn::GfxSetting::sInstance, 0);
    }

    bool RainbowInkUpdate::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(RainbowInkUpdate)
	
    RainbowInkPatch::RainbowInkPatch() {
        this->patch = {
            {0x02043de8, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) repl_calcInkColor, 0x02043de8), "cmpwi r6, 0")},

			// Team 0
			//{0x0203ea00, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_calcInkColor, 0x0203ea00), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) calcInkColor, 0x0203ea00))},
			// Team 1
			//{0x0203eaa0, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_calcInkColor_2, 0x0203eaa0), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) calcInkColor, 0x0203eaa0))},

        };
    }

    bool RainbowInkPatch::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(RainbowInkPatch)

    void RainbowInkWrapper::start() {
		RainbowInkUpdate *rainbowInkUpdateModule = silverlightInstance->m_moduleStates.getModule<RainbowInkUpdate>();
		RainbowInkPatch *rainbowInkPatchModule = silverlightInstance->m_moduleStates.getModule<RainbowInkPatch>();

		rainbowInkUpdateModule->m_enabled = true;
		rainbowInkPatchModule->enablePatch();
    }

    void RainbowInkWrapper::stop() {
		RainbowInkUpdate *rainbowInkUpdateModule = silverlightInstance->m_moduleStates.getModule<RainbowInkUpdate>();
		RainbowInkPatch *rainbowInkPatchModule = silverlightInstance->m_moduleStates.getModule<RainbowInkPatch>();

		rainbowInkUpdateModule->m_enabled = false;
		rainbowInkPatchModule->disablePatch();
	}

    void RainbowInkWrapper::update(float deltaTime) {
    }

    bool RainbowInkWrapper::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(RainbowInkWrapper)
}
