//
// Created by tv on 04.11.23.
//
#include"forcenetworkeddamage.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    ForceNetworkedDamage::ForceNetworkedDamage() {
        this->patch = {
                {0x0267B884, PatchElement("li r0, 1", "lbz r0, 0x44(r12)")},
        };
    }

    bool ForceNetworkedDamage::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(ForceNetworkedDamage)
}
