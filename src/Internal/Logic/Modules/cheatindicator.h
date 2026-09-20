#pragma once

#include<Internal/Logic/modules.h>
#include<nn/swkbd.h>

namespace Modules {
    class CheatIndicator : public Modules::UpdateModule {
    VCLASS(CheatIndicator, ESC({&Modules::UpdateModule::classInfo, nullptr}))

    public:
        bool cheatsEnabled;

        CheatIndicator();

        void start() override;

        void stop() override;

        void update(float deltaTime) override;

        void render(float deltaTime) override;

        bool isCheatModule() override;
    };
}
