//
// Created by tv on 15.11.23.
//

#pragma once


#include "Internal/Logic/UpdateModule.h"

class BlasterShooterRapidfire : public Modules::UpdateModule {
VCLASS(BlasterShooterRapidfire, ESC({&UpdateModule::classInfo, nullptr}))
public:
    void start() override;

    void stop() override;

    bool isCheatModule() override;

public:
    void update(float deltaTime) override;
};
