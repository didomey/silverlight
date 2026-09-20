#include"futurefly.h"
#include "Shared/Core/Logging.h"
#include "Shared/Cafe/vpad.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<vpad/input.h>
#include<glm/mat3x3.hpp>
#include<Game/Assembler/ppcAssembler.h>
#include "noclipeverywhere.h"
#include "Internal/silverlight.h"

namespace Modules {
    void FutureFly::start() {
        m_lastPlayerPosition = g_playerMgr->m_player1Position;

        NoclipEverywhereUpdate *noclipEverywhereUpdateModule = silverlightInstance->m_moduleStates.getModule<NoclipEverywhereUpdate>();
        //this->noclipEverywhereUpdateModulePreviouslyEnabled = noclipEverywhereUpdateModule->m_enabled;

        NoclipEverywherePatch *noclipEverywherePatchModule = silverlightInstance->m_moduleStates.getModule<NoclipEverywherePatch>();
        this->noclipEverywherePatchModulePreviouslyEnabled = noclipEverywherePatchModule->m_enabled;

        //noclipEverywhereUpdateModule->m_enabled = true;
        //noclipEverywherePatchModule->enablePatch();
    }

    void FutureFly::stop() {
        NoclipEverywhereUpdate *noclipEverywhereUpdateModule = silverlightInstance->m_moduleStates.getModule<NoclipEverywhereUpdate>();
        //noclipEverywhereUpdateModule->m_enabled = this->noclipEverywhereUpdateModulePreviouslyEnabled;

        NoclipEverywherePatch *noclipEverywherePatchModule = silverlightInstance->m_moduleStates.getModule<NoclipEverywherePatch>();
        //noclipEverywherePatchModule->m_enabled = this->noclipEverywherePatchModulePreviouslyEnabled;
		//noclipEverywherePatchModule->apply();
    }

    void FutureFly::update(float deltaTime) {
        if (!g_playerMgr->m_playerBehindCamera)
            return;

        VPADStatus status = {};
        VPADReadError err;

        VPADRead(VPAD_CHAN_0, &status, 1, &err);

        Inputs *inputs = (Inputs *) &status.hold;

        if (inputs->ButtonZL)
            m_lastPlayerPosition.y -= deltaTime * 200;
        else if (inputs->ButtonX)
            m_lastPlayerPosition.y += deltaTime * 200;

        glm::vec3 moveDirRelative = {
                status.leftStick.y,
                0.0f,
                -status.leftStick.x
        };

        glm::vec3 forwardDir = g_playerMgr->m_playerBehindCamera->m_playerMoveRotation;
        glm::vec3 upDir = {0.0f, 1.0f, 0.0f};
        glm::vec3 rightDir = glm::cross(upDir, forwardDir);

        glm::mat3x3 rotationMatrix = {
                forwardDir,
                upDir,
                rightDir
        };

        glm::vec3 moveDirection = rotationMatrix * moveDirRelative;

        m_lastPlayerPosition.x += moveDirection.x * deltaTime * 200;
        m_lastPlayerPosition.z += moveDirection.z * deltaTime * 200;

        g_playerMgr->m_player1Position = m_lastPlayerPosition;
    }

    bool FutureFly::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(FutureFly)
}
