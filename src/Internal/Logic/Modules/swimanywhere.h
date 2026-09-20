//
// Created by tv on 15.11.23.
//

#pragma once

#include<Internal/Logic/UpdateModule.h>

class SwimAnywhere : public Modules::UpdateModule {
VCLASS(SwimAnywhere, ESC({&UpdateModule::classInfo, nullptr}))
public:
    void start() override;

    void stop() override;

    void update(float deltaTime) override;

    bool isCheatModule() override;
};
