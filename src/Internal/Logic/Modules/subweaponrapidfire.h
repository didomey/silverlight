//
// Created by tv on 17.11.23.
//

#pragma once

#include<Internal/Logic/UpdateModule.h>

class SubWeaponRapidfire : public Modules::UpdateModule {
VCLASS(SubWeaponRapidfire, ESC({&UpdateModule::classInfo, nullptr}))
public:
    void start() override;

    void stop() override;

    void update(float deltaTime) override;

    bool isCheatModule() override;
};
