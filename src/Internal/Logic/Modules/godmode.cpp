//
// Created by tv on 04.11.23.
//
#include"godmode.h"
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    GodMode::GodMode() {
        this->patch = {{0x0268078c, PatchElement("blr", "stwu r1, -0x80(r1)")}};
    }

    bool GodMode::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(GodMode)
}
