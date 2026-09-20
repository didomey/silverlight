#pragma once

#include<Internal/Logic/modules.h>

namespace Modules {
    class MainWeapon : public Modules::UpdateModule {
    VCLASS(MainWeapon, ESC({&Modules::UpdateModule::classInfo, nullptr}))

    private:
        MainWeapon();

        void start() override;

        void stop() override;

        void update(float deltaTime) override;

        bool isCheatModule() override;
    };

    class SubWeapon : public Modules::UpdateModule {
    VCLASS(SubWeapon, ESC({&Modules::UpdateModule::classInfo, nullptr}))

    private:
        SubWeapon();

        void start() override;

        void stop() override;

        void update(float deltaTime) override;

        bool isCheatModule() override;
    };

    class SpecialWeapon : public Modules::UpdateModule {
    VCLASS(SpecialWeapon, ESC({&Modules::UpdateModule::classInfo, nullptr}))

    private:
        SpecialWeapon();

        void start() override;

        void stop() override;

        void update(float deltaTime) override;

        bool isCheatModule() override;
    };

	class CustomWeapon : public PatchModule {
    VCLASS(CustomWeapon, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        CustomWeapon();
    };
}
