#include"Assembly.h"
#include"AssemblyRegistry.h"
#include"ReflectableClass.h"
#include "Shared/Core/Logging.h"
#include<iostream>

namespace Refl {


    Assembly::Assembly(const char *name) {
        m_nativeAssembly = std::make_unique<NativeAssembly>(name);

        GetAsmFunc InfoGetter = (GetAsmFunc) m_nativeAssembly->getExport("get" + std::string(name) + "AssemblyInfo");

        if (InfoGetter == nullptr) {
            CAFEERROR("Unable to find assembly info!");
            return;
        }
        m_info = InfoGetter();
    }

    std::vector<const ClassInfo *> Assembly::getAllSubclasses(const ClassInfo &info) {
        std::vector<const ClassInfo *> output;

        for (auto classinfo: m_info->m_classes) {
            if (classinfo->isSubclassOf(info))
                output.push_back(classinfo);
        }


        return output;
    }

    FirstAssemblyRegistrationHelper::FirstAssemblyRegistrationHelper(GetAsmFunc getAsmFunc) {
        getAssemblyRegistry()->selfRegister(getAsmFunc());
    }
}