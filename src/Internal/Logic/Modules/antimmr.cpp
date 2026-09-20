//
// Created by tv on 04.11.23.
//
#include"antimmr.h"
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    AntiMMR::AntiMMR() {
        this->patch = {
			{0x021B1B14, PatchElement("li r3, 0", "mr r3, r31")}
		};
		this->enablePatch();
    }

    bool AntiMMR::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(AntiMMR)
}
