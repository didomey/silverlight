//
// Created by tv on 04.11.23.
//

#pragma once



namespace Modules {
    class MatchTime : public PatchModule {
        VCLASS(MatchTime, ESC({&PatchModule::classInfo,nullptr}))
        uint32_t calcMatchTime() {

        }

    protected:

    public:
        MatchTime();
    };
}
