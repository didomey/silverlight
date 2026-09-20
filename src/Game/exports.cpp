//
// Created by tv on 03.11.23.
//

#include<Internal/silverlight.h>
#include <coreinit/dynload.h>
#include "Shared/Core/Logging.h"
#include<Shared/Reflection/AssemblyRegistry.h>

#include "Shared/CemuBind.h"

extern "C" void __init();

extern "C" void initSilverlight() {
    __init();

	LoadCemuSLSymbols();

    Refl::getAssemblyRegistry()->flushQueue();
    new Silverlight();
}
//Takes in extra parameters because this function replaces the first text rendering call inside the Memory Display
extern "C" void updateSilverlight(uint32_t unk1, const char *text, uint32_t unk2) {
    if (unk1 == 0)
        return;
    silverlightInstance->update(unk1, unk2);
}
