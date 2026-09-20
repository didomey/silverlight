#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include "aimassist.h"


namespace Modules {

    void AimAssist::start() {
    }

    void AimAssist::stop() {
        g_playerMgr->m_unk6 = 0;
    }

    void AimAssist::update(float deltaTime) {
        if (g_playerMgr == nullptr)
            return;


        if (g_playerMgr->m_unk2 == nullptr)
            return;

        if (g_playerMgr->m_unk2->m_chargeState != 0) {
            g_playerMgr->m_unk6 = 0;
            return;
        }

        g_playerMgr->m_unk6 = 9999;
    }

    bool AimAssist::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AimAssist)
}
