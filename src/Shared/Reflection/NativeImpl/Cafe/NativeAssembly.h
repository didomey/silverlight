//
// Created by tv on 09.08.23.
//

#ifndef ENGINE_NATIVEASSEMBLYIMPL_H
#define ENGINE_NATIVEASSEMBLYIMPL_H


#include <Shared/Reflection/NativeImpl/NativeAssembly.h>
#include<filesystem>
#include<iostream>
#include<coreinit/dynload.h>
#include "Shared/Core/Logging.h"

namespace Refl {
    NativeAssembly::NativeAssembly(std::string name) {
        OSDynLoad_Error err = OSDynLoad_Acquire(name.c_str(), &m_internals.m_assembly);

        if (err != OS_DYNLOAD_OK)
            CAFECRASH("Unable to load assembly: " + name + "\n ERROR CODE: " + std::to_string(err));

        m_name = name;
    }

    void *NativeAssembly::getExport(const std::string &name) {
        void *func = nullptr;

        OSDynLoad_Error err = OSDynLoad_FindExport(m_internals.m_assembly, OS_DYNLOAD_EXPORT_FUNC, name.c_str(), &func);

        if (err != OS_DYNLOAD_OK)
            CAFECRASH("Unable to find export: " + name + "\n ERROR CODE: " + std::to_string(err));

        return func;
    }

    NativeAssembly::~NativeAssembly() {
        //dlclose(m_internals.m_assembly);
    }
}
#endif //ENGINE_NATIVEASSEMBLYIMPL_H
