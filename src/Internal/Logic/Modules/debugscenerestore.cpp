//
// Created by tv on 04.11.23.
//
#include"debugscenerestore.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    DebugSceneRestore::DebugSceneRestore() {
        this->patch = {
			{ 0x1003127c, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x100311f8, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x100311b0, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x10031210, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x100311ec, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x10031204, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x100311bc, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x10031198, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x1003124c, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x10031270, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x100311e0, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x100311c8, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x10031258, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x10031224, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x10031234, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x1003121c, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x100311a4, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x100311d4, PatchElement((void*) 0x021f8818, (void*) 0x0) },
			{ 0x10031264, PatchElement((void*) 0x021f8818, (void*) 0x0) },
        };
        this->enablePatch();
    }

    bool DebugSceneRestore::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DebugSceneRestore)
}
