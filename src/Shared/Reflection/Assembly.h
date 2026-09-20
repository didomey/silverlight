//
// Created by tv on 09.08.23.
//

#ifndef VMIRROR_ASSEMBLY_H
#define VMIRROR_ASSEMBLY_H

#include<memory>
#include"NativeImpl/NativeAssembly.h"
#include<unordered_map>
#include<vector>

#if !defined(VASSEMBLYNAME)// && !defined(VREFL_SELF_OVERRIDE)
#   error No assembly name specified via compiler
#endif

#ifdef VMIRROR_SELF_OVERRIDE
#   define VMIRROR_OVERRIDE true
#   define VMIRROR_ASSEMBLYNAME "NONE"
#   warning VMirror self override is enabled THIS IS ONLY FOR USE BY VMIRROR ITSELF
#endif

namespace Refl {

    struct ClassInfo;

#pragma pack(push, 1)

    struct AssemblyVersion {
        const unsigned char m_major;
        const unsigned char m_minor;
        const unsigned char m_revision;
        const unsigned char m_patch;

        inline bool operator==(const AssemblyVersion &other) const {
            return (other.m_major == m_major) &&
                   (other.m_minor == m_minor) &&
                   (other.m_revision == m_revision) &&
                   (other.m_patch == m_patch);
        }
    };

#pragma pack(pop)

    enum class AssemblyType {
        Executable = 0b10,
        DynamicLibrary = 0b01,
        StaticLibrary = 0b11
    };

    struct AssemblyInfo {
        const std::string m_name;
        const AssemblyVersion m_version;
        const AssemblyType m_type;
        const bool m_automaticRegistry;
        //Class register
        std::vector<const ClassInfo *> m_classes;
    };

    struct Assembly {
        Assembly(const char *name);

        inline Assembly(AssemblyInfo *info) {
            m_info = info;
        }

        AssemblyInfo *m_info;
        std::unique_ptr<NativeAssembly> m_nativeAssembly;

        std::vector<const ClassInfo *> getAllSubclasses(const ClassInfo &info);
    };

    typedef AssemblyInfo *(*GetAsmFunc)();

    struct FirstAssemblyRegistrationHelper {
        FirstAssemblyRegistrationHelper(GetAsmFunc getAsmFunc);
    };

}


#define VASSEMBLY(name, version, type) \
extern "C"{                                                                                             \
    Refl::AssemblyInfo* get##name##AssemblyInfo(){                                                   \
        static Vir::Refl::AssemblyInfo name##AssemblyInfo = Refl::AssemblyInfo{ #name,version,type,false };  \
        return & name##AssemblyInfo;                                                                    \
    }                                                                                                   \
}

#define VASSEMBLYSELFREGISTER(name, version, type) \
extern "C"{                                                                                             \
    Refl::AssemblyInfo* get##name##AssemblyInfo(){                                                   \
        static Refl::AssemblyInfo name##AssemblyInfo = Refl::AssemblyInfo{ #name,version,type,false };  \
        return & name##AssemblyInfo;                                                                    \
    }                                                                                                   \
}                                                      \
volatile static Refl::FirstAssemblyRegistrationHelper name##RegistrationHelper = Refl::FirstAssemblyRegistrationHelper(get##name##AssemblyInfo);

#define VASSEMBLYVERSION(major, minor, revision, patch) Refl::AssemblyVersion{major,minor,revision,patch}

#endif //VMIRROR_ASSEMBLY_H
