//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/modules.h"
#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class NeutralTeamFix : public PatchModule {
    VCLASS(NeutralTeamFix, ESC({&PatchModule::classInfo, nullptr}))
    public:

        bool isCheatModule() override;

        NeutralTeamFix();
    };

    class WorldCrashFix : public PatchModule {
    VCLASS(WorldCrashFix, ESC({&PatchModule::classInfo, nullptr}))
    public:

        bool isCheatModule() override;

        WorldCrashFix();
    };

    class LoadBulletsEverywhere : public PatchModule {
    VCLASS(LoadBulletsEverywhere, ESC({&PatchModule::classInfo, nullptr}))
    public:

        bool isCheatModule() override;

        LoadBulletsEverywhere();
    };

    class PlazaCrashFix : public PatchModule {
    VCLASS(PlazaCrashFix, ESC({&PatchModule::classInfo, nullptr}))
    public:

        bool isCheatModule() override;

        PlazaCrashFix();
    };

    class OctolingFixPatch : public PatchModule {
    VCLASS(OctolingFixPatch, ESC({&PatchModule::classInfo, nullptr}))
    public:
        OctolingFixPatch();

        bool isCheatModule() override;
    };

    class OctolingFixUpdate : public UpdateModule {
    VCLASS(OctolingFixUpdate, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        OctolingFixUpdate();

        void start() override;

        void stop() override;

        bool isCheatModule() override;
    };

    class InkMineRapidFireCrashFix : public PatchModule {
    VCLASS(InkMineRapidFireCrashFix, ESC({&PatchModule::classInfo, nullptr}))
    public:
        InkMineRapidFireCrashFix();

        bool isCheatModule() override;
    };

    class AboveFourPlayersTeamCrashFix : public PatchModule {
    VCLASS(AboveFourPlayersTeamCrashFix, ESC({&PatchModule::classInfo, nullptr}))
    public:
        AboveFourPlayersTeamCrashFix();

        bool isCheatModule() override;
    };

    class InvalidObjectCrashFix : public PatchModule {
    VCLASS(InvalidObjectCrashFix, ESC({&PatchModule::classInfo, nullptr}))
    public:
        InvalidObjectCrashFix();

        bool isCheatModule() override;
    };

    class Plaza60FPS : public PatchModule {
    VCLASS(Plaza60FPS, ESC({&PatchModule::classInfo, nullptr}))
    public:
        Plaza60FPS();

        bool isCheatModule() override;
    };

    class EnableRainmakerSpecial : public PatchModule {
    VCLASS(EnableRainmakerSpecial, ESC({&PatchModule::classInfo, nullptr}))
    public:
        EnableRainmakerSpecial();

        bool isCheatModule() override;
    };

    class ShowFloorCrashFix : public PatchModule {
    VCLASS(ShowFloorCrashFix, ESC({&PatchModule::classInfo, nullptr}))
    public:
        ShowFloorCrashFix();

        bool isCheatModule() override;
    };

    class GetPerformerAtCrashFix : public PatchModule {
    VCLASS(GetPerformerAtCrashFix, ESC({&PatchModule::classInfo, nullptr}))
    public:
        GetPerformerAtCrashFix();

        bool isCheatModule() override;
    };

    class MissionOnlineFixes : public PatchModule {
    VCLASS(MissionOnlineFixes, ESC({&PatchModule::classInfo, nullptr}))
    public:
        MissionOnlineFixes();

        bool isCheatModule() override;
    };
}
