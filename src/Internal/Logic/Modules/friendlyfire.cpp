//
// Created by tv on 04.11.23.
//
#include"friendlyfire.h"
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    FriendlyFire::FriendlyFire() {
        this->patch = {
			//{0x0264f910, PatchElement("blr", "mflr r0")},
			//{0x02647c58, PatchElement("blr", "mflr r0")}
			{0x02645de0, PatchElement("li r3, 1", "mflr r0")},
			{0x02645de4, PatchElement("blr", "stwu r1, -0x18(r1)")},
		};
    }

    bool FriendlyFire::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(FriendlyFire)
}
