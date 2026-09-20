// General fixes for in-game crashes
// warning: this code is cringe!




#include"initialpatches.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include<Game/Macros.h>
#include <Game/Globals/player.h>

FUNCBINDUNK(02419cc8, int(*)(int param_1, int * param_2));

void repl_LAB_02419cc4(int param_1, int *param_2) {
    if (param_1 < 0x1000) {
        return;
    }

    // replaced instruction
    __asm__(
        "lwz 12,4(3)"
    );

    FUN_02419cc8(param_1, param_2);
}

void __world00_loc_0x0() {
    __asm__(
        R"(
		lwz 3, 0x55E4(11)
		cmpwi 3, 0
		beq bctr_0253E0CC
		)"
            B(0x0253, 0xe074)
            "bctr_0253E0CC:"
            B(0x0253, 0xE0CC)
            );
}

void __world00_loc_0x2() {
    __asm__(
            R"(
		lis 25, 0x101F
		cmpwi 6, 0
		beq bctr_02539FC8
		)"
            B(0x0253, 0x9e98)
            "bctr_02539FC8:"
            B(0x0253, 0xE0CC)
            );
}

void __plaza00_loc_0x0() {
    __asm__(
            R"(
		cmpwi 12, 0;
		beq bctr_02536964;
		lwz 0, 0x0b38(12);
		)"
            B(0x0253, 0x693c)
            "bctr_02536964:"
            B(0x0253, 0x6964)
            );
}

void __plaza00_loc_0x2() {
    __asm__(
            R"(
		cmpwi 8, 0;
		beq bctr_02559660;
		lwz 0, 0x0b40(8);)"
            B(0x0255, 0x9638)
            "bctr_02559660:"
            B(0x0255, 0x9660)
            );
}

void __plaza00_loc_0x4() {
    __asm__(
            R"(
		cmpwi 12, 0;
		beq bctr_0259e71c;
		lwz 3, 0x2f4(12);)"
            B(0x0259, 0xe6bc)
            "bctr_0259e71c:"
            B(0x0259, 0xe71c)
            );
}

void __plaza00_loc_0x6() {
    __asm__(
            R"(
		lis 28, 0x101e;
		lwz 28, 0x4ae0(28);
		cmpwi 28, 0;
		beqlr-;
		stwu 1, -0x120(1);)"
            B(0x0255, 0x9b7c)
            );
}

void repl_LAB_0222DCA4() {
    __asm__(
            R"(
		mulli 28,30,40;
		mr 5,28;
		li 4,29;
		mr 3,17;
		bl bctr_02239EE0;
		li 5,120;
		li 4,39;
		mr 3,17;
		bl bctr_02239F38;
		li 5,36;
		li 4,50;
		mr 3,17;
		bl bctr_0223AD50;
		mulli 5,30,11;
		li 4,111;
		mr 3,17;
		bl bctr_0223AA38;
		mulli 5,30,11;
		li 4,112;
		mr 3,17;
		bl bctr_0223AA90;
		mulli 5,30,11;
		li 4,113;
		mr 3,17;
		bl bctr_0223AAE8;
		mulli 5,30,11;
		li 4,114;
		mr 3,17;
		bl bctr_0223AB40;
		mulli 27,30,10;
		mr 5,27;
		li 4,120;
		mr 3,17;
		bl bctr_0223AB98;
		mr 5,27;
		li 4,121;
		mr 3,17;
		bl bctr_0223ABF0;
		mr 5,27;
		li 4,122;
		mr 3,17;
		bl bctr_0223AC48;
		mr 5,27;
		li 4,123;
		mr 3,17;
		bl bctr_0223ACA0;
		mulli 24,30,24;
		mr 5,24;
		li 4,24;
		mr 3,17;
		bl bctr_02239D28;
		mr 5,24;
		li 4,25;
		mr 3,17;
		bl bctr_02239D80;
		mr 5,24;
		li 4,26;
		mr 3,17;
		bl bctr_02239DD8;
		mr 5,24;
		li 4,27;
		mr 3,17;
		bl bctr_02239E30;
		mulli 5,30,5;
		li 4,36;
		mr 3,17;
		bl bctr_02239E88;
		mulli 5,29,8;
		li 4,124;
		mr 3,17;
		bl bctr_0223A300;
		mulli 5,30,8;
		li 4,81;
		mr 3,17;
		bl bctr_0223C038;
		mulli 5,30,4;
		li 4,83;
		mr 3,17;
		bl bctr_0223C090;
		mulli 5,30,10;
		li 4,76;
		mr 3,17;
		bl bctr_0223A6C8;
		li 4,135;
		b bctr_0222DCA8;
		)"
            "bctr_02239EE0:"
            B(0x0223, 0x9EE0)
            "bctr_02239F38:"
            B(0x0223, 0x9F38)
            "bctr_0223AD50:"
            B(0x0223, 0xAD50)
            "bctr_0223AA38:"
            B(0x0223, 0xAA38)
            "bctr_0223AA90:"
            B(0x0223, 0xAA90)
            "bctr_0223AAE8:"
            B(0x0223, 0xAAE8)
            "bctr_0223AB40:"
            B(0x0223, 0xAB40)
            "bctr_0223AB98:"
            B(0x0223, 0xAB98)
            "bctr_0223ABF0:"
            B(0x0223, 0xABF0)
            "bctr_0223AC48:"
            B(0x0223, 0xAC48)
            "bctr_0223ACA0:"
            B(0x0223, 0xACA0)
            "bctr_02239D28:"
            B(0x0223, 0x9D28)
            "bctr_02239D80:"
            B(0x0223, 0x9D80)
            "bctr_02239DD8:"
            B(0x0223, 0x9DD8)
            "bctr_02239E30:"
            B(0x0223, 0x9E30)
            "bctr_02239E88:"
            B(0x0223, 0x9E88)
            "bctr_0223A300:"
            B(0x0223, 0xA300)
            "bctr_0223C038:"
            B(0x0223, 0xC038)
            "bctr_0223C090:"
            B(0x0223, 0xC090)
            "bctr_0223A6C8:"
            B(0x0223, 0xA6C8)
            "bctr_0222DCA8:"
            B(0x0222, 0xDCA8)
            );
}

void repl_LAB_0222D7C0() {
    __asm__(
            R"(
		cmpwi 11, 0
		beq bullet_codecave_beq
		cmpwi 11, 6
		beq bullet_codecave_beq
		cmpwi 11, 8
		beq bullet_codecave_beq
		cmpwi 11, 9
		beq bullet_codecave_beq
		cmpwi 11, 14
		bne bullet_codecave_bne
		b bullet_codecave_beq
)"
            "bullet_codecave_bne:"
            B(0x0222, 0xDCDC)
            "bullet_codecave_beq:"
            B(0x0222, 0xD7C8)
            );
}

void repl_LAB_025E1D48() {
	__asm__(
		R"(
		cmpwi 31, 0
		mr 3, 31
		beq bctr_025e1d50
		)"
		B(0x025e, 0x1d4c)
		"bctr_025e1d50:"
		B(0x025e, 0x1d50)
	);
}

void repl_LAB_02758F5C() {
	__asm__(
		R"(
		cmpwi 31, 0
		beq bctr_02758F60
		stw 9, 0(31)
		)"
		B(0x0275, 0x8f60)
		"bctr_02758F60:"
		B(0x0275, 0x8f60)
	);
}

void getPerformerAtCrashFix() {
	__asm__(
		R"(
		cmpwi 3, 0
		beq end
		mr 28, 3
		)"
		B(0x0263, 0x5c98)
		"end:"
		B(0x0263, 0x5cd0)
	);
}

namespace Modules {
    NeutralTeamFix::NeutralTeamFix() {
        this->patch = {
                /*
                {0x02419cc4, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) repl_LAB_02419cc4, 0x02419cc4), "lwz 12, 0x4 (3)")},
                {0x0285c1f0, PatchElement("cmpw 7, 13", "cmpwi 7, 0")},
                */
        };
        this->enablePatch();
    }

    bool NeutralTeamFix::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(NeutralTeamFix)

    WorldCrashFix::WorldCrashFix() {
        this->patch = {
                {0x0253E06C, PatchElement(
                        DynamicBranchReplacementSingle(BranchType::Branch, (void *) __world00_loc_0x0, 0x0253E06C),
                        "cmpwi r0, 3")},
                {0x02559634, PatchElement("nop", "lwz r3, 0x55e4(11)")},
                {0x02539E94, PatchElement(
                        DynamicBranchReplacementSingle(BranchType::Branch, (void *) __world00_loc_0x2, 0x02539E94),
                        "lis r25, 0x101f")}
        };
        this->enablePatch();
    }

    bool WorldCrashFix::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(WorldCrashFix)

    LoadBulletsEverywhere::LoadBulletsEverywhere() {
        // TODO: only apply if in PB to prevent crash from reaching memory limit
        this->patch = {
                {0x0222D7C0, PatchElement(
                        DynamicBranchReplacementSingle(BranchType::Branch, (void *) repl_LAB_0222D7C0, 0x0222D7C0),
                        "cmpwi r11, 0x8")},
                {0x0222DCA4, PatchElement(
                        DynamicBranchReplacementSingle(BranchType::Branch, (void *) repl_LAB_0222DCA4, 0x0222DCA4),
                        "li r4, 0x87")},
        };
        //this->enablePatch();
    }

    bool LoadBulletsEverywhere::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(LoadBulletsEverywhere)

    PlazaCrashFix::PlazaCrashFix() {
        this->patch = {
                {0x02536938, PatchElement(
                        DynamicBranchReplacementSingle(BranchType::Branch, (void *) __plaza00_loc_0x0, 0x02536938),
                        "lwz r0, 0xb38(r12)")},
                {0x02559634, PatchElement(
                        DynamicBranchReplacementSingle(BranchType::Branch, (void *) __plaza00_loc_0x2, 0x02559634),
                        "lwz r0, 0xb40(r8)")},
                {0x0259e6b8, PatchElement(
                        DynamicBranchReplacementSingle(BranchType::Branch, (void *) __plaza00_loc_0x4, 0x0259e6b8),
                        "lwz r3, 0x2f4(r12)")},
                {0x02559b78, PatchElement(
                        DynamicBranchReplacementSingle(BranchType::Branch, (void *) __plaza00_loc_0x6, 0x02559b78),
                        "stwu r1, -0x120(r1)")}
        };
        this->enablePatch();
    }

    bool PlazaCrashFix::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(PlazaCrashFix)

    OctolingFixPatch::OctolingFixPatch() {
        this->patch = {
                {0x021a8f74, PatchElement("nop", "stw r0, 0x34(r29)")},
        };
        this->enablePatch();
    }

    bool OctolingFixPatch::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(OctolingFixPatch)

    OctolingFixUpdate::OctolingFixUpdate() {
		this->m_enabled = true;
    }

    void OctolingFixUpdate::start() {
        PLAYER_CTRL_VOICE_BANK = (char *) "Other";
    }

    void OctolingFixUpdate::stop() {
        PLAYER_CTRL_VOICE_BANK = (char *) "PlayerCtrl";
    }

    bool OctolingFixUpdate::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(OctolingFixUpdate)

    InkMineRapidFireCrashFix::InkMineRapidFireCrashFix() {
        this->patch = {
                {0x025e1d48, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void *) repl_LAB_025E1D48, 0x025e1d48), "mr r3, r31")},
        };
        this->enablePatch();
    }

    bool InkMineRapidFireCrashFix::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(InkMineRapidFireCrashFix)

    InvalidObjectCrashFix::InvalidObjectCrashFix() {
        this->patch = {
                {0x0243ECAC, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchIfGreaterThan, (void *) 0x0243ECD4, 0x0243ECAC), DynamicBranchReplacementSingle(BranchType::BranchIfGreaterThan, (void *) 0x0243ecbc, 0x0243ECAC))},
        };
        this->enablePatch();
    }

    bool InvalidObjectCrashFix::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(InvalidObjectCrashFix)

    AboveFourPlayersTeamCrashFix::AboveFourPlayersTeamCrashFix() {
        this->patch = {
                {0x02758F5C, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void *) repl_LAB_02758F5C, 0x02758F5C), "stw r9, 0x0(r31)")},
        };
        this->enablePatch();
    }

    bool AboveFourPlayersTeamCrashFix::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(AboveFourPlayersTeamCrashFix)

    Plaza60FPS::Plaza60FPS() {
        this->patch = {
                {0x0242B09C, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::Branch, (void *) 0x0242a8f8, 0x0242B09C))},
        };
        this->enablePatch();
    }

    bool Plaza60FPS::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(Plaza60FPS)

    EnableRainmakerSpecial::EnableRainmakerSpecial() {
        this->patch = {
                {0x024CB1D8, PatchElement("li r0, 0", "lbz r0, 0x34f(r29)")},
                {0x0269C88C, PatchElement("li r3, 5", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02632414, 0x0269c88c))},
        };
        this->enablePatch();
    }

    bool EnableRainmakerSpecial::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(EnableRainmakerSpecial)

    ShowFloorCrashFix::ShowFloorCrashFix() {
        this->patch = {
                {0x021588f8, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02161d00, 0x021588f8))},
        };
        this->enablePatch();
    }

    bool ShowFloorCrashFix::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(ShowFloorCrashFix)

	// Bubbler
    GetPerformerAtCrashFix::GetPerformerAtCrashFix() {
        this->patch = {
                {0x02635C94, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) getPerformerAtCrashFix, 0x02635C94), "mr r28, r3")},
        };
        this->enablePatch();
    }

    bool GetPerformerAtCrashFix::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(GetPerformerAtCrashFix)

    MissionOnlineFixes::MissionOnlineFixes() {
        this->patch = {
			// Msn MapObjs in VSGame
            {0x0257393C, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) 0x02573968, 0x0257393C), DynamicBranchReplacementSingle(BranchType::BranchIfLessThan, (void*) 0x02574978, 0x0257393C))},
            {0x02573964, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchIfNotEqual, (void*) 0x02574978, 0x02573964))},

			// Enemies in VSGame
            {0x0232aa9c, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) 0x0232AADC, 0x0232aa9c), DynamicBranchReplacementSingle(BranchType::BranchIfEqual, (void*) 0x0232aadc, 0x0232aa9c))},
            {0x02573964, PatchElement("li r0, 1", "lbz r0, 0x44(r12)")},

			// Items in VSGame
            {0x0246ff38, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) 0x0246ff44, 0x0246ff38), DynamicBranchReplacementSingle(BranchType::BranchIfEqual, (void*) 0x0246ff44, 0x0246ff38))},
            {0x0246ff6c, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) 0x0246ffa4, 0x0246ff6c), DynamicBranchReplacementSingle(BranchType::BranchIfEqual, (void*) 0x0246ffa4, 0x0246ff6c))},
            {0x0246f3b8, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) 0x0246f3d0, 0x0246f3b8), DynamicBranchReplacementSingle(BranchType::BranchIfEqual, (void*) 0x0246f3d0, 0x0246f3b8))},
            {0x02470098, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) 0x024700fc, 0x02470098), DynamicBranchReplacementSingle(BranchType::BranchIfEqual, (void*) 0x024700fc, 0x02470098))},
        };

        this->disablePatch();
    }

    bool MissionOnlineFixes::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(MissionOnlineFixes)
}
