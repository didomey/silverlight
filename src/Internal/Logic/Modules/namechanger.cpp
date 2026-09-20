#include<Internal/Logic/modules.h>
#include<nn/swkbd.h>
#include "Internal/silverlight.h"
#include "namechanger.h"
#include "Shared/Cafe/swkbd.h"
#include "Shared/strop.h"

#include "Internal/Draw/rendering.h"

namespace Modules {
    class InitialNameChanger : UpdateModule {
    VCLASS(InitialNameChanger, ESC({&UpdateModule::classInfo, nullptr}))
    private:
        InitialNameChanger() { m_enabled = true; };

        void start() override {};

        void stop() override {};

        void update(float deltaTime) override;

        bool isCheatModule() override { return false; };
    };

    REGISTERVCLASS(InitialNameChanger)

    void InitialNameChanger::update(float deltaTime) {
        std::array<char16_t, 11> tempName = {};
        uint32_t ptr = *((uint32_t *) 0x101E80A4);
        char *text = (char *) (ptr + 0x8C);

        memcpy(tempName.data(), text, 22);

        memcpy(text, u"[SL] ", 10);

        memcpy(text + 10, tempName.data(), 22);

        toggle();
    }


    NameChanger::NameChanger() {
    }

    void NameChanger::start() {
        silverlightInstance->m_menuControl = false;

        nn::swkbd::AppearArg appearArg;
        appearArg.keyboardArg.configArg.languageType = nn::swkbd::LanguageType::English;
        appearArg.keyboardArg.configArg.disableNewLine = false;
        appearArg.inputFormArg.hintText = u"Name";
        if (!nn::swkbd::AppearInputForm(appearArg)) {
            CAFEERRORSHOW("Unable to open keyboard")

            return;
        }
    }

    void NameChanger::stop() {

        nn::swkbd::DisappearInputForm();

        silverlightInstance->m_menuControl = true;
    }

    void NameChanger::update(float deltaTime) {
        if (Cafe::Swkbd::update()) {
            if (nn::swkbd::IsDecideOkButton(nullptr)) {
                std::u16string str = nn::swkbd::GetInputFormString();

                uint32_t ptr = *((uint32_t *) 0x101E80A4);

                if (0x10600000 < ptr &&
                    ptr < 0x1D000000) {

                    //emplace string 4 characters into the players name
                    char *text = (char *) (ptr + 0x8C);

                    unsigned int size = std::min(str.size() * 2 + 2, 32u - 10u);

                    memcpy(text + 10, str.data(), size);
                }

                toggle();
            } else if (nn::swkbd::IsDecideCancelButton(nullptr))
                toggle();
        }
    }

    bool NameChanger::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(NameChanger)

	void NameChanger::render(float deltaTime) {
		uint32_t ptr = *((uint32_t *) 0x101E80A4);

        if (0x10600000 < ptr &&
            ptr < 0x1D000000) {
            char16_t *text = (char16_t *) (ptr + 0x8C);

            if (text != nullptr) {
                std::u16string u16str = text;

        		silverlightInstance->m_renderer.setTextCursor({-625, -300});
                silverlightInstance->m_renderer.drawText("Name:");

				std::string str = u16string_to_string(u16str);

				if (str.rfind("[SL] ", 0) == 0) {
					str = str.substr(5, str.length() - 1);
					silverlightInstance->m_renderer.setTextCursor({-575, -300});
					silverlightInstance->m_renderer.drawTextRainbow("[SL]");
				}

        		silverlightInstance->m_renderer.setTextCursor({-535, -300});
                silverlightInstance->m_renderer.drawText(str);
            }
        }
	}
}
