//
// Created by tv on 04.11.23.
//
#include"showcopyrighttext.h"
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
	ShowCopyrightText::ShowCopyrightText() {
		this->m_enabled = true;
	}

    void ShowCopyrightText::start() {
    }

    void ShowCopyrightText::stop() {
    }

    void ShowCopyrightText::update(float deltaTime) {
	}

    void ShowCopyrightText::render(float deltaTime) {
		silverlightInstance->m_renderer.setTextCursor({325, -325});
    	silverlightInstance->m_renderer.drawText("(c) Splatoon Decomp Lab 2024");
	}

    bool ShowCopyrightText::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(ShowCopyrightText)
}
