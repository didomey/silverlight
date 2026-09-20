#ifndef MY_FIRST_RPL_H
#define MY_FIRST_RPL_H

#include<memory>
#include<Game/StaticMem.h>
#include<Game/MainMgr.h>
#include "Internal/Logic/modules.h"
#include<chrono>
#include"Draw/rendering.h"
#include<random>

class Menu {
public:
    virtual void draw() = 0;

    virtual void click() = 0;

    virtual void cursorUp() = 0;

    virtual void cursorDown() = 0;
};

class Silverlight {
public:
    Silverlight();

    void update(uint32_t unk1, uint32_t unk2);

    void draw(float deltaTime);

    Modules::ModuleState m_moduleStates;

    std::chrono::high_resolution_clock::time_point m_lastUpdate;

    Renderer m_renderer;

    std::shared_ptr<Menu> m_topLevelMenu;

    std::shared_ptr<Menu> m_menu;

    float m_averageFps = 60.0f;

    bool m_drawMenu = true;
    bool m_menuControl = true;

    bool m_displayName = false;

    std::default_random_engine m_generator;

    bool m_currentlyInPublicMatch = false;
};

inline std::unique_ptr<Silverlight> silverlightInstance;

#endif // MY_FIRST_RPL_H
