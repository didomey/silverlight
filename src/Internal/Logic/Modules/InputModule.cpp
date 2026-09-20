//
// Created by tv on 18.12.23.
//
#include"InputModule.h"
#include "Shared/Cafe/swkbd.h"
#include<Internal/silverlight.h>
#include<nn/swkbd.h>

namespace Modules {
    InputModule::InputModule() {
    }

    void InputModule::start() {
        silverlightInstance->m_menuControl = false;

        nn::swkbd::AppearArg appearArg;
        appearArg.keyboardArg.configArg.languageType = nn::swkbd::LanguageType::English;
        appearArg.keyboardArg.configArg.disableNewLine = false;
        appearArg.inputFormArg.hintText = u"Value";
        if (!nn::swkbd::AppearInputForm(appearArg)) {
            CAFEERRORSHOW("Unable to open keyboard")

            return;
        }
    }

    void InputModule::stop() {

        nn::swkbd::DisappearInputForm();

        silverlightInstance->m_menuControl = true;
    }

    void InputModule::update(float deltaTime) {
        if (Cafe::Swkbd::update()) {
            if (nn::swkbd::IsDecideOkButton(nullptr)) {
                std::u16string str = nn::swkbd::GetInputFormString();

                receivedEntry(str);

                toggle();
            } else if (nn::swkbd::IsDecideCancelButton(nullptr))
                toggle();
        }
    }

    bool InputModule::isCheatModule() {
        return false;
    }

    REGISTERABSTRACTVCLASS(InputModule)
}
