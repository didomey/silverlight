#pragma once

#include<Internal/Logic/modules.h>

namespace Modules {
    class WeaponChanger : public Modules::UpdateModule {
    VCLASS(WeaponChanger, ESC({&Modules::UpdateModule::classInfo, nullptr}))

    private:
        WeaponChanger();

        void start() override;

        void stop() override;

        void update(float deltaTime) override;

        bool isCheatModule() override;
    };
}
