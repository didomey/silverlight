#include<Internal/Logic/modules.h>
#include<nn/swkbd.h>

#include "Internal/silverlight.h"

#include "displaymessage.h"
#include "cheatindicator.h"

#include "Shared/strop.h"

namespace Modules {
    REGISTERVCLASS(DisplayMessage)

    void DisplayMessage::start() {
    }

    void DisplayMessage::stop() {
    }

    void DisplayMessage::update(float deltaTime) {
    }

    void DisplayMessage::render(float deltaTime) {
        DisplayMessageInput *displayMessageInputModule = silverlightInstance->m_moduleStates.getModule<DisplayMessageInput>();

        std::string text = u16string_to_string(displayMessageInputModule->text);

        CheatIndicator *cheatIndicatorModule = silverlightInstance->m_moduleStates.getModule<CheatIndicator>();

        if (!cheatIndicatorModule) {
            return;
        }

        int yPos = 350;

        if (cheatIndicatorModule->cheatsEnabled) {
            yPos -= 25;
        }

        if (!text.empty()) {
            silverlightInstance->m_renderer.setTextCursor({-(text.length() * 9.600006 / 2), yPos});
            silverlightInstance->m_renderer.drawText(text);
        }
    }

    bool DisplayMessage::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DisplayMessageInput)

    void DisplayMessageInput::start() {
        silverlightInstance->m_menuControl = false;

        nn::swkbd::AppearArg appearArg;
        appearArg.keyboardArg.configArg.languageType = nn::swkbd::LanguageType::English;
        appearArg.inputFormArg.hintText = u"Text";
        if (!nn::swkbd::AppearInputForm(appearArg)) {
            CAFEERRORSHOW("Unable to open keyboard")

            return;
        }
    }

    void DisplayMessageInput::stop() {
        nn::swkbd::DisappearInputForm();

        silverlightInstance->m_menuControl = true;
    }

    void DisplayMessageInput::update(float deltaTime) {
        VPADStatus vpadStatus;
        VPADRead(VPAD_CHAN_0, &vpadStatus, 1, nullptr);

        nn::swkbd::ControllerInfo controllerInfo;
        controllerInfo.vpad = &vpadStatus;
        controllerInfo.kpad[0] = nullptr;
        controllerInfo.kpad[1] = nullptr;
        controllerInfo.kpad[2] = nullptr;
        controllerInfo.kpad[3] = nullptr;
        nn::swkbd::Calc(controllerInfo);

        if (nn::swkbd::IsNeedCalcSubThreadFont()) {
            nn::swkbd::CalcSubThreadFont();
        }

        if (nn::swkbd::IsNeedCalcSubThreadPredict()) {
            nn::swkbd::CalcSubThreadPredict();
        }

        nn::swkbd::DrawTV();
        nn::swkbd::DrawDRC();


        if (nn::swkbd::IsDecideOkButton(nullptr) || nn::swkbd::IsDecideCancelButton(nullptr)) {
            std::u16string str = nn::swkbd::GetInputFormString();

            this->text = str;

            toggle();
        }
    }

    bool DisplayMessageInput::isCheatModule() {
        return false;
    }
}
