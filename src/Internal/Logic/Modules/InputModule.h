//
// Created by tv on 18.12.23.
//

#pragma once

#include<Internal/Logic/modules.h>

namespace Modules {
    class InputModule : public Modules::UpdateModule {
    VABSTRACTCLASS(InputModule, ESC({&Modules::UpdateModule::classInfo, nullptr}))

    public:
        InputModule();

        void start() override;

        void stop() override;

        void update(float deltaTime) override;

        bool isCheatModule() override;

        virtual void receivedEntry(const std::u16string &input) = 0;
    };

#define INMODULE(modulename) \
    class modulename : public InputModule {\
    VCLASS(modulename, ESC({&InputModule::classInfo, nullptr}))\
    void receivedEntry(const std::u16string &input) override;\
    };                           \
    REGISTERVCLASS(MapNameInput) \
    void modulename::receivedEntry(const std::u16string &input)
}
