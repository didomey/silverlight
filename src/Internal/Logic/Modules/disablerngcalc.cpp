//
// Created by tv on 04.11.23.
//
#include"disablerngcalc.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    DisableRNGCalc::DisableRNGCalc() {
        this->patch = {
            {0x028fc0dc, PatchElement("li r3, 0", "lwz r6, 0xc(r3)")},
            {0x028fc0e0, PatchElement("blr", "lwz r11, 0x0(r3)")},
        };
    }

    bool DisableRNGCalc::isCheatModule() {
        return true;
    }

	std::string DisableRNGCalc::helpText() {
		return "Disables all RNG in the game; makes all RNG functions return 0.";
	}

    REGISTERVCLASS(DisableRNGCalc)
}
