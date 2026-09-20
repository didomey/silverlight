//
// Created by tv on 04.11.23.
//

#pragma once



namespace Modules {
    class PlayerEsp : public PatchModule {
    VCLASS(PlayerEsp, ESC({&PatchModule::classInfo, nullptr}))
    public:
        PlayerEsp();

        bool isCheatModule() override;
    };
}
