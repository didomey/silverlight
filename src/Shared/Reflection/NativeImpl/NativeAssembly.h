//
// Created by tv on 09.08.23.
//

#ifndef ENGINE_NATIVEASSEMBLY_H
#define ENGINE_NATIVEASSEMBLY_H

#include<string>


#   include"Cafe/NativeAssemblyInternals.h"

namespace Refl {
    class NativeAssembly {
    public:
        NativeAssembly(std::string name);

        void *getExport(const std::string &name);

        std::string m_name;

        virtual ~NativeAssembly();

    private:
        NativeAssemblyInternals m_internals;
    };
}

#endif //ENGINE_NATIVEASSEMBLY_H
