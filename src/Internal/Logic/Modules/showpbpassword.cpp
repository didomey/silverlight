//
// Created by tv on 04.11.23.
//
#include"showpbpassword.h"
#include "Shared/Core/Logging.h"
#include "Shared/Cafe/vpad.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include"Game/MainMgr.h"
#include<vpad/input.h>
#include<glm/mat3x3.hpp>
#include<Game/Assembler/ppcAssembler.h>
#include"Game/StaticMem.h"
#include "setscenehook.h"
#include "Internal/silverlight.h"

namespace Modules {
    ShowPBPassword::ShowPBPassword() {
        this->m_enabled = true;
    }

    void ShowPBPassword::start() {

    }

    void ShowPBPassword::stop() {

    }

    void ShowPBPassword::render(float deltaTime) {
		// if is pb
		if (currSceneId == 5) {
            std::string dispText = "Pass: " + std::to_string(g_staticMem->m_password);

            silverlightInstance->m_renderer.setTextCursor({-325, -325});
            silverlightInstance->m_renderer.drawText(dispText);
		}
    }

    void ShowPBPassword::update(float deltaTime) {
    }

    bool ShowPBPassword::isCheatModule() {
        return false;
    }


    REGISTERVCLASS(ShowPBPassword)
}
