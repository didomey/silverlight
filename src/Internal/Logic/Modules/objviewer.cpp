//
// Created by tv on 04.11.23.
//
#include"objviewer.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    ObjViewer::ObjViewer() {
        this->patch = {
                {0x023f9a34, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02a4c36c, 0x023f9a34))},
        };
    }

    bool ObjViewer::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(ObjViewer)
}
