//
// Created by tv on 04.11.23.
//
#include"zeropaint.h"
#include "Shared/Core/Logging.h"
#include "Shared/Cafe/vpad.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<vpad/input.h>
#include<glm/mat3x3.hpp>
#include<Game/Assembler/ppcAssembler.h>

namespace Modules {
    ZeroPaint::ZeroPaint() {
		this->m_enabled = true;
    }

    void ZeroPaint::start() {
    }

    void ZeroPaint::stop() {

    }

    void ZeroPaint::update(float deltaTime) {
        if (g_playerMgr == nullptr)
            return;

        g_playerMgr->m_turfPaint = 0;
    }

    bool ZeroPaint::isCheatModule() {
        return false;
    }


    REGISTERVCLASS(ZeroPaint)
}
