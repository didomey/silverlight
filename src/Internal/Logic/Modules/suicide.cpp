#include <Game/MainMgr.h>

namespace Modules {
    void suicide() {
        if (g_playerMgr == nullptr)
            return;
        g_playerMgr->m_hex4E0Unk = 0xC0;
    }
}
