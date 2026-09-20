#pragma once

#include "Internal/Logic/UpdateModule.h"
#include<glm/vec3.hpp>
#include <vector>
#include "Game/MainMgrBase.h"
#include "Internal/Logic/Modules/playereventhook.h"

namespace Modules {
	class NoKrnlHook : public PatchModule {
    VCLASS(NoKrnlHook, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;
        bool allowDisable() override;

        NoKrnlHook();
    };
}
