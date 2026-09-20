#include"splatfestbutton.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    SplatfestButton::SplatfestButton() {
        this->patch = {
			{0x027F1D84, PatchElement("li r9, 0", "lbz r9, 0x282(r8)") },
			{0x027F1DC4, PatchElement("cmpwi r11, 5", "cmpwi r11, 0x4") },
			{0x027F1E0C, PatchElement("li r12, 0", "lbz r12, 0x282(r6)") },
			{0x027F1E40, PatchElement("cmplwi r0, 6", "lwz r0, 0x5") },
			{0x027F1E8C, PatchElement("li r8, 0", "lbz r8, 0x282(r3)") },
			{0x027F1F10, PatchElement("addi r9,r9, 6", "addi r9, r9, 0x5") },
			{0x027F1F14, PatchElement("lis r0, 0x2AAA", "addi r0, r0, 0x6666") },
			{0x027F1F18, PatchElement("ori r0, r0, 0xAAAB", "ori r0, r0, 0x6667") }
        };
        this->enablePatch();
    }

    bool SplatfestButton::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(SplatfestButton)
}
