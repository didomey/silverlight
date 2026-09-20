//
// Created by tv on 18.11.23.
//

#pragma once

#include "Shared/Core/Logging.h"

namespace Modules {

    template<class T>
    T *ModuleState::getModule() {
        if (T::classInfo.isSubclassOf(UpdateModule::classInfo)) {
            return (T *) getUpdateModule(T::VReflName);
        } else if (T::classInfo.isSubclassOf(PatchModule::classInfo)) {
            return (T *) getPatchModule(T::VReflName);
        }

        return nullptr;
    }
}
