//
// Created by tv on 04.11.23.
//

#pragma once


#include "Internal/Logic/UpdateModule.h"
#include "Internal/Logic/modules.h"
#include "InputModule.h"

namespace Modules {
	class CustomLevelInput : public InputModule {
    VCLASS(CustomLevelInput, ESC({&InputModule::classInfo, nullptr}))
		void receivedEntry(const std::u16string &input) override;
    };

    class CustomLevel : public PatchModule {
    VCLASS(CustomLevel, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        CustomLevel();
    };

	class CustomLevelExpInput : public InputModule {
    VCLASS(CustomLevelExpInput, ESC({&InputModule::classInfo, nullptr}))
		void receivedEntry(const std::u16string &input) override;
    };

    class CustomLevelExp : public PatchModule {
    VCLASS(CustomLevelExp, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        CustomLevelExp();
    };

	class CustomRankInput : public InputModule {
    VCLASS(CustomRankInput, ESC({&InputModule::classInfo, nullptr}))
		void receivedEntry(const std::u16string &input) override;
    };

    class CustomRank : public PatchModule {
    VCLASS(CustomRank, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        CustomRank();
    };

	class CustomRankPointsInput : public InputModule {
    VCLASS(CustomRankPointsInput, ESC({&InputModule::classInfo, nullptr}))
		void receivedEntry(const std::u16string &input) override;
    };

    class CustomRankPoints : public PatchModule {
    VCLASS(CustomRankPoints, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        CustomRankPoints();
    };

	class CustomMoneyInput : public InputModule {
    VCLASS(CustomMoneyInput, ESC({&InputModule::classInfo, nullptr}))
		void receivedEntry(const std::u16string &input) override;
    };

    class CustomMoney : public PatchModule {
    VCLASS(CustomMoney, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        CustomMoney();
    };

	class CustomFestRankInput : public InputModule {
    VCLASS(CustomFestRankInput, ESC({&InputModule::classInfo, nullptr}))
		void receivedEntry(const std::u16string &input) override;
    };

    class CustomFestRank : public PatchModule {
    VCLASS(CustomFestRank, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        CustomFestRank();
    };

	class CustomFestRankPointsInput : public InputModule {
    VCLASS(CustomFestRankPointsInput, ESC({&InputModule::classInfo, nullptr}))
		void receivedEntry(const std::u16string &input) override;
    };

    class CustomFestRankPoints : public PatchModule {
    VCLASS(CustomFestRankPoints, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        CustomFestRankPoints();
    };

	class CustomFestTeamInput : public InputModule {
    VCLASS(CustomFestTeamInput, ESC({&InputModule::classInfo, nullptr}))
		void receivedEntry(const std::u16string &input) override;
    };

    class CustomFestTeam : public PatchModule {
    VCLASS(CustomFestTeam, ESC({&PatchModule::classInfo, nullptr}))
    public:
        bool isCheatModule() override;

        CustomFestTeam();
    };
}
