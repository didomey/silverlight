#pragma once

#include <cstdint>
#include<string>
#include<vector>
#include"InputModule.h"

struct Map {
    std::string dispName;
    std::string internalName;
};

inline std::vector<Map> g_maps = {
        {"Mahi-Mahi Resort",           "Fld_Hiagari00_Vss"},
        {"Saltspray Rig",              "Fld_SeaPlant00_Vss"},
        {"Urchin Underpass",           "Fld_Crank00_Vss"},
        {"Walleye Warehouse",          "Fld_Warehouse00_Vss"},
        {"Camp Triggerfish",           "Fld_Athletic00_Vss"},
        {"Port Mackerel",              "Fld_Amida00_Vss"},
        {"Kelp Dome",                  "Fld_Maze00_Vss"},
        {"Moray Towers",               "Fld_Tuzura00_Vss"},
        {"Bluefin Depot",              "Fld_Ruins00_Vss"},
        {"Ancho-V Games",              "Fld_Office00_Vss"},
        {"Piranha Pit",                "Fld_Quarry00_Vss"},
        {"Flounder Heights",           "Fld_Jyoheki00_Vss"},
        {"Museum d'Alfonsino",         "Fld_Pivot00_Vss"},
        {"Hammerhead Bridge",          "Fld_Kaisou00_Vss"},
        {"Fld_Hiagari00_Vss",          "Fld_Hiagari00_Vss"},
        {"Fld_SeaPlant00_Vss",         "Fld_SeaPlant00_Vss"},
        {"Fld_Crank00_Vss",            "Fld_Crank00_Vss"},
        {"Fld_Warehouse00_Vss",        "Fld_Warehouse00_Vss"},
        {"Fld_Athletic00_Vss",         "Fld_Athletic00_Vss"},
        {"Fld_Amida00_Vss",            "Fld_Amida00_Vss"},
        {"Fld_Maze00_Vss",             "Fld_Maze00_Vss"},
        {"Fld_Tuzura00_Vss",           "Fld_Tuzura00_Vss"},
        {"Fld_Ruins00_Vss",            "Fld_Ruins00_Vss"},
        {"Fld_Office00_Vss",           "Fld_Office00_Vss"},
        {"Fld_Quarry00_Vss",           "Fld_Quarry00_Vss"},
        {"Fld_Jyoheki00_Vss",          "Fld_Jyoheki00_Vss"},
        {"Fld_Pivot00_Vss",            "Fld_Pivot00_Vss"},
        {"Fld_Kaisou00_Vss",           "Fld_Kaisou00_Vss"},
        {"Fld_World00_Wld",            "Fld_World00_Wld"},
        {"Fld_Plaza00_Plz",            "Fld_Plaza00_Plz"},
        {"Fld_EasyHide00_Msn",         "Fld_EasyHide00_Msn"},
        {"Plaza",                      "Fld_Plaza00_Plz"},
        {"Shooting Range",             "Fld_ShootingRange_Shr"},
        {"Tutorial",                   "Fld_Tutorial00_Ttr"},
        {"Tutorial Show",              "Fld_TutorialShow00_Ttr"},
        {"Credits/Staffroll",          "Fld_StaffRoll00_Stf"},
        // dojo/duels
        {"Urchin Underpass Dojo",      "Fld_Crank00_Dul"},
        {"Walleye Warehouse Dojo",     "Fld_Warehouse00_Dul"},
        {"Saltspray Rig Dojo",         "Fld_SeaPlant00_Dul"},
        {"Arowana Mall Dojo",          "Fld_UpDown00_Dul"},
        {"Blackbelly Skatepark Dojo",  "Fld_SkatePark00_Dul"},
        {"Singleplayer Overworld",     "Fld_World00_Wld"},

        {"Octotrooper Hideout",        "Fld_EasyHide00_Msn"},
        {"Lair of the Octoballs",      "Fld_EasyClimb00_Msn"},
        {"Rise of the Octocopters",    "Fld_EasyJump00_Msn"},
        {"The Mighty Octostomp",       "Fld_BossStampKing_Bos_Msn"},

        {"Gusher Gauntlet",            "Fld_Geyser00_Msn"},
        {"Floating Sponge Garden",     "Fld_Sponge00_Msn"},
        {"Propeller Lift Playground",  "Fld_Propeller00_Msn"},
        {"Spreader Splatfest",         "Fld_PaintingLift00_Msn"},
        {"Octoling Invasion",          "Fld_RvlMaze00_Msn"},
        {"Unidentified Flying Object", "Fld_OctZero00_Msn"},
        {"The Dreaded Octonozzle",     "Fld_BossCylinderKing_Bos_Msn"},

        {"Inkrail Skyscape",           "Fld_InkRail00_Msn"},
        {"Inkvisible Avenues",         "Fld_Invisible00_Msn"},
        {"Flooder Junkyard",           "Fld_Dozer00_Msn"},
        {"Shifting Splatforms",        "Fld_SlideLift00_Msn"},
        {"Octoling Assault",           "Fld_RvlSkatePark00_Msn"},
        {"Undeniable Flying Object",   "Fld_OctRuins00_Msn"},
        {"The Rampaging Octowhirl!",   "Fld_BossBallKing_Bos_Msn"},

        {"Propeller Lift Fortress",    "Fld_Propeller01_Msn"},
        {"Octosniper Ramparts",        "Fld_Charge00_Msn"},
        {"Tumbling Splatforms",        "Fld_TurnLift00_Msn"},
        {"Octoling Uprising",          "Fld_RvlRuins00_Msn"},
        {"Unwelcome Flying Object",    "Fld_OctCrank00_Msn"},
        {"The Ravenous Octomaw!",      "Fld_BossMouthKing_Bos_Msn"},

        {"Switch Box Shake-Up",        "Fld_Trance00_Msn"},
        //{"Spongy Observatory",         "Fld_Sponge01_Msn"},
        {"Pinwheel Power Plant",       "Fld_Fusya00_Msn"},
        {"Far-Flung Flooders",         "Fld_Dozer01_Msn"},
        {"Octoling Onslaught",         "Fld_RvlSeaPlant00_Msn"},
        {"Unavoidable Flying Object",  "Fld_OctSkatePark00_Msn"},
        {"Enter the Octobot King!",    "Fld_BossRailKing_Bos_Msn"},

		{"Observatory",                "Fld_Observatory00_Vss"},
};

struct Scene {
    std::string name;
    uint32_t id;
};

inline std::vector<Scene> g_scenes = {
        {"Boot",                           0},
        {"Plaza",                          1},
        {"Lobby",                          2},
        {"Match",                          3},
        {"Match (cNone/Match/PartyMatch)", 4},
        {"PrivateMatch",                   5},
        {"TeamMatch",                      6},
        {"VSGame",                         7},
        {"Mission",                        8},
        {"World",                          9},
        {"Dojo (Duel)",                    10},
        {"ShootingRange",                  11},
        {"Recon",                          12},
        {"StaffRoll",                      13},
        {"Shop",                           14},
        {"Customize",                      15},
        {"WalkThrough",                    16},
        {"Dojo (DuelSetting)",             17},
        {"DayChange",                      18},
        {"Tutorial",                       19},
        {"EndingPlaza",                    20},
        {"MiniGame",                       21},
        {"TitleForShow",                   22},
        {"LobbyForShow",                   23},
        {"MatchForShow",                   24},
        {"TutForShow",                     25},
        {"ThanksForShow",                  26},
        {"DbgEntry",                       27},
        {"DbgSetting",                     28},
        {"DummyMatch",                     29},
        {"DummyTeamMatch",                 30},
        {"Viewer",                         31},
        {"FreeTest",                       43},
};

inline std::string g_nextMap = "Fld_Crank00_Vss";
inline uint32_t g_nextSceneId = 0;


namespace Modules {
    class SceneNameInput : public InputModule {
    VCLASS(SceneNameInput, ESC({&InputModule::classInfo, nullptr}))

        void receivedEntry(const std::u16string &input) override;
    };

}

void switchScene(uint32_t sceneId);
