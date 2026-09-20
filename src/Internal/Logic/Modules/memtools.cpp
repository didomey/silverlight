#include<Internal/Logic/modules.h>
#include<nn/swkbd.h>
#include "Internal/silverlight.h"
#include "memtools.h"
#include "Shared/Cafe/swkbd.h"
#include "Game/Assembler/ppcAssembler.h"
#include "Shared/strop.h"
#include "Internal/Menus/DirectoryMenu.h"

#define DATA_START 0x101dcba0
#define DATA_END 0x101e9713

#define BSS_START 0x101ea000
#define BSS_END 0x1026f56b

namespace Modules {
	namespace MemUtils {
		std::vector<uint32_t> scan(int32_t start, int32_t end, std::vector<uint8_t> targetBytes, int allignment) {
			std::vector<uint32_t> res = {};

			for (uint32_t i = start; i < end; i += allignment) {
				uint8_t* data = (uint8_t*)i;
				if (!data) continue;

				uint32_t j = 0;

				bool dataIsIdentical = true;

				while (dataIsIdentical && j < targetBytes.size()) {
					if (i + j >= end) { 
						dataIsIdentical = false;
						break;
					}

					if (data[j] != targetBytes[j]) {
						dataIsIdentical = false;
					}
					j++;
				}

				if (dataIsIdentical) {
					res.push_back(i);
				}
			}

			return res;
		}
	}

    SearchForBytesInput::SearchForBytesInput() {
		this->locatedLocations = {};
    }

    void SearchForBytesInput::start() {
        silverlightInstance->m_menuControl = false;

        nn::swkbd::AppearArg appearArg;
        appearArg.keyboardArg.configArg.languageType = nn::swkbd::LanguageType::English;
        appearArg.keyboardArg.configArg.disableNewLine = false;
        appearArg.inputFormArg.hintText = u"Enter opcode to assemble";
        if (!nn::swkbd::AppearInputForm(appearArg)) {
            CAFEERRORSHOW("Unable to open keyboard")
            return;
        }
    }

    void SearchForBytesInput::stop() {
        nn::swkbd::DisappearInputForm();

        silverlightInstance->m_menuControl = true;
    }

    void SearchForBytesInput::update(float deltaTime) {
        if (Cafe::Swkbd::update()) {
            if (nn::swkbd::IsDecideOkButton(nullptr)) {
                std::string str = u16string_to_string(nn::swkbd::GetInputFormString());

				CAFEASSERT(str.length() % 2 == 0);

				std::vector<uint8_t> byteArray = {0};

				for (size_t i = 0; i < str.length(); i += 2) {
					std::string byteString = str.substr(i, 2);

					CAFEINFO(byteString.c_str());

					uint8_t byte;
					std::istringstream(byteString) >> std::hex >> byte;

					byteArray.push_back(byte);
				}

				std::vector<uint32_t> dataResults = MemUtils::scan(DATA_START, DATA_END, byteArray, 4);
				std::vector<uint32_t> bssResults = MemUtils::scan(BSS_START, BSS_END, byteArray, 4);

				this->locatedLocations = {};
				this->locatedLocations.insert(locatedLocations.end(), dataResults.begin(), dataResults.end());
				this->locatedLocations.insert(locatedLocations.end(), bssResults.begin(), bssResults.end());

				toggle();
            } else if (nn::swkbd::IsDecideCancelButton(nullptr))
                toggle();
        }
    }

    bool SearchForBytesInput::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(SearchForBytesInput)

	SearchForBytes::SearchForBytes() {
		this->m_enabled = true;
    }

	void SearchForBytes::start() {
    }

	void SearchForBytes::stop() {
    }

	void SearchForBytes::render(float deltaTime) {
		Menus::DirectoryMenu* topLevelMenu = dynamic_cast<Menus::DirectoryMenu*>(silverlightInstance->m_topLevelMenu.get());

		if (!topLevelMenu) return;

		if (topLevelMenu->m_selectionIdx == 13) {
			auto *searchForBytesInputModule = silverlightInstance->m_moduleStates.getModule<SearchForBytesInput>();

			std::string text = "Search Result(s):";
			int yPos = 275;

			silverlightInstance->m_renderer.setTextCursor({-(text.length() * 9.600006 / 2), yPos});
			silverlightInstance->m_renderer.drawText(text);

			int i = 0;

			for (const auto &address : searchForBytesInputModule->locatedLocations) {
				if (i > 24) {
					break;
				}

				text = toHexString(address);
				yPos -= 25;

				silverlightInstance->m_renderer.setTextCursor({-(text.length() * 9.600006 / 2), yPos});
				silverlightInstance->m_renderer.drawText(text);

				i++;
			}
		}
    }

    bool SearchForBytes::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(SearchForBytes)

    BreakpointInput::BreakpointInput() {
		this->locatedLocations = {};
    }

    void BreakpointInput::start() {
        silverlightInstance->m_menuControl = false;

        nn::swkbd::AppearArg appearArg;
        appearArg.keyboardArg.configArg.languageType = nn::swkbd::LanguageType::English;
        appearArg.keyboardArg.configArg.disableNewLine = false;
        appearArg.inputFormArg.hintText = u"Enter opcode to assemble";
        if (!nn::swkbd::AppearInputForm(appearArg)) {
            CAFEERRORSHOW("Unable to open keyboard")
            return;
        }
    }

    void BreakpointInput::stop() {
        nn::swkbd::DisappearInputForm();

        silverlightInstance->m_menuControl = true;
    }

    void BreakpointInput::update(float deltaTime) {
        if (Cafe::Swkbd::update()) {
            if (nn::swkbd::IsDecideOkButton(nullptr)) {
                std::string str = u16string_to_string(nn::swkbd::GetInputFormString());

				CAFEASSERT(str.length() % 2 == 0);

				std::vector<uint8_t> byteArray = {0};

				for (size_t i = 0; i < str.length(); i += 2) {
					std::string byteString = str.substr(i, 2);

					CAFEINFO(byteString.c_str());

					uint8_t byte;
					std::istringstream(byteString) >> std::hex >> byte;

					byteArray.push_back(byte);
				}
            } else if (nn::swkbd::IsDecideCancelButton(nullptr))
                toggle();
        }
    }

    bool BreakpointInput::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(BreakpointInput)
}
