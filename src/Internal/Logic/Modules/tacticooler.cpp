//
// Created by tv on 04.11.23.
//
#include"tacticooler.h"
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    Tacticooler::Tacticooler() {
        this->patch = {
			{0x026883E0, PatchElement("li r0, 6", "lwz r0, 0x8(r1)")},
			{0x026883EC, PatchElement("li r0, 1", "lwz r0, 0x8f0(r30)")},
		};
    }

    bool Tacticooler::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(Tacticooler)
}
