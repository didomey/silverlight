//
// Created by tv on 04.11.23.
//
#include"splatfestmode.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include "Game/Globals/music.h"
#include "Internal/Logic/modules.h"
#include "Internal/Logic/UpdateModule.h"
#include "Game/StaticMem.h"
#include "Game/Unk.h"

namespace Modules {
    SplatfestModePatch::SplatfestModePatch() {
		this->patch = {
			{0x0217D960, PatchElement("li r0, 1", "lwz r0, 0x0(r7)")},
			{0x021e7978, PatchElement("nop", 
				DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x021e7980, 0x021e7978)
			)},
			{0x02178ff4, PatchElement("nop", 
				DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x02179000, 0x02178ff4)
			)},
			{0x02750fa4, PatchElement("nop", 
				DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x02750fb4, 0x02750fa4)
			)},
			{0x024e26b0, PatchElement("nop", 
				DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x024e26ec, 0x024e26b0)
			)},
			{0x024e2184, PatchElement("nop", 
				DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x024e2390, 0x024e2184)
			)},
			{0x02750e60, PatchElement("nop", 
				DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x02750eb4, 0x02750e60)
			)},
			{0x02750f08, PatchElement("nop", 
				DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x02750f54, 0x02750f08)
			)},
			{0x024d91bc, PatchElement("nop", 
				DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x024d91cc, 0x024d91bc)
			)},
			{0x024e31a4, PatchElement("nop", 
				DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x024e33e4, 0x024e31a4)
			)},
			{0x024e3644, PatchElement("nop", 
				DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x024e3690, 0x024e3644)
			)},
			{0x024e3644, PatchElement("nop", 
				DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x024e3690, 0x024e3644)
			)},


			{0x028c23fc, PatchElement("li r3, 1", "mflr r0")},
			{0x028c2400, PatchElement("blr", "stwu r0, 0x4(r1)")},

		};
    }

    bool SplatfestModePatch::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(SplatfestModePatch)

	void SplatfestModeUpdate::start() {
		*REGULAR_MUSIC_1 = *FEST_MUSIC_1;
		*REGULAR_MUSIC_2 = *FEST_MUSIC_1;
		*REGULAR_MUSIC_3 = *FEST_MUSIC_1;
		*REGULAR_MUSIC_4 = *FEST_MUSIC_1;
		*REGULAR_MUSIC_5 = *FEST_MUSIC_1;
		*REGULAR_MUSIC_6 = *FEST_MUSIC_1;
		*REGULAR_MUSIC_7 = *FEST_MUSIC_1;
		*REGULAR_MUSIC_8 = *FEST_MUSIC_1;
    }

    void SplatfestModeUpdate::stop() {
    }

    void SplatfestModeUpdate::update(float deltaTime) {
		getStaticMem()->m_hour = 1;
		getStaticMem()->m_bgmId = -1;
		getStaticMem()->m_bgmSeed = 0;
	}

    bool SplatfestModeUpdate::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(SplatfestModeUpdate)

	void SplatfestModeWrapper::start() {
		SplatfestModeUpdate *splatfestModeUpdateModule = silverlightInstance->m_moduleStates.getModule<SplatfestModeUpdate>();
		SplatfestModePatch *splatfestModePatchModule = silverlightInstance->m_moduleStates.getModule<SplatfestModePatch>();

		splatfestModeUpdateModule->enable();
		splatfestModePatchModule->enablePatch();
    }

    void SplatfestModeWrapper::stop() {
		SplatfestModeUpdate *splatfestModeUpdateModule = silverlightInstance->m_moduleStates.getModule<SplatfestModeUpdate>();
		SplatfestModePatch *splatfestModePatchModule = silverlightInstance->m_moduleStates.getModule<SplatfestModePatch>();

		splatfestModeUpdateModule->disable();
		splatfestModePatchModule->disablePatch();
    }

    void SplatfestModeWrapper::update(float deltaTime) {
	}

    bool SplatfestModeWrapper::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(SplatfestModeWrapper)
}
