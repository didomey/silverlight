#pragma once

#include<Internal/Logic/modules.h>
#include<nn/swkbd.h>

namespace Modules {
    class DisplayMessageInput;

    class DisplayMessage : public Modules::UpdateModule {
    VCLASS(DisplayMessage, ESC({&Modules::UpdateModule::classInfo, nullptr}))

    private:
        DisplayMessage() {

        }

        void start() override;

        void stop() override;

        void update(float deltaTime) override;

        void render(float deltaTime) override;

        bool isCheatModule() override;
    };

    class DisplayMessageInput : public Modules::UpdateModule {
    VCLASS(DisplayMessageInput, ESC({&Modules::UpdateModule::classInfo, nullptr}))

    protected:
        std::u16string text;

    private:
        DisplayMessageInput() {

        }

        void start() override;

        void stop() override;

        void update(float deltaTime) override;

        bool isCheatModule() override;

        friend class DisplayMessage;
    };
}
