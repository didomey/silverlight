//
// Created by tv on 04.11.23.
//
#include"subweaponsalwaysusable.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    SubWeaponsAlwaysUsable::SubWeaponsAlwaysUsable() {
        this->patch = {
                {0x026367B8, PatchElement("li r3, 0", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x0262d7f4, 0x026367B8))},
                {0x026379A4, PatchElement("li r27, 0", "li r27, 1")},
        };
    }

    bool SubWeaponsAlwaysUsable::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(SubWeaponsAlwaysUsable)
}
