//
// Created by tv on 09.08.23.
//

#ifndef ENGINE_NATIVEASSEMBLYINTERNALS_H
#define ENGINE_NATIVEASSEMBLYINTERNALS_H

#include<coreinit/dynload.h>

namespace Refl {
    struct NativeAssemblyInternals {
        OSDynLoad_Module m_assembly;
    };
}

#endif //ENGINE_NATIVEASSEMBLYINTERNALS_H
