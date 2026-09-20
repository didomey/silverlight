//
// Created by tv on 23.12.23.
//

#pragma once

#include<Internal/silverlight.h>

#define CHEAT_CHECK \
if (silverlightInstance->m_currentlyInPublicMatch) {\
for (const auto &module: silverlightInstance->m_moduleStates.m_updateModules) {\
if (module->m_enabled && module->isCheatModule()) {\
module->toggle();\
}\
}\
for (const auto &module: silverlightInstance->m_moduleStates.m_patchModules) {\
if (module->m_enabled && module->isCheatModule()) {\
module->toggle();\
}\
}\
}
