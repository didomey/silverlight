#include <Game/MainMgr.h>
#include "Internal/silverlight.h"

namespace Modules {
    void flipTeam() {
        if (silverlightInstance->m_currentlyInPublicMatch)
            return;
        if (g_playerMgr == nullptr)
            return;
        //g_mainMgr->m_teamId < 3 ? g_mainMgr->m_teamId++ : g_mainMgr->m_teamId = 0;
        g_playerMgr->m_teamId ^= true;
    }
}
