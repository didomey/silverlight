#pragma once

#include<Internal/Logic/modules.h>
#include<nn/swkbd.h>
#include "Internal/silverlight.h"

namespace Modules {
    class NameChanger : public Modules::UpdateModule {
    VCLASS(NameChanger, ESC({&Modules::UpdateModule::classInfo, nullptr}))

    private:
        NameChanger();

        void start() override;

        void stop() override;

        void render(float deltaTime) override;

        void update(float deltaTime) override;

        bool isCheatModule() override;
    };
}
