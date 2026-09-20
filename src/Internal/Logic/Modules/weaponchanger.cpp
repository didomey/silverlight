#include<Internal/Logic/modules.h>
#include<nn/swkbd.h>
#include "Internal/silverlight.h"
#include "weaponchanger.h"
#include "Shared/Cafe/swkbd.h"
#include <Game/weapons.h>
#include <Shared/strop.h>
#include<Game/MainMgr.h>

namespace Modules {
    WeaponChanger::WeaponChanger() {
    }

    void WeaponChanger::start() {
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

    void WeaponChanger::stop() {

        nn::swkbd::DisappearInputForm();

        silverlightInstance->m_menuControl = true;
    }

    void WeaponChanger::update(float deltaTime) {
        if (Cafe::Swkbd::update()) {
            if (nn::swkbd::IsDecideOkButton(nullptr)) {
                std::u16string str = nn::swkbd::GetInputFormString();


                std::string requestedWeapon = u16string_to_string(str);

                WeaponInfo &closestMatch = findClosestMatch<WeaponInfo>(requestedWeapon, c_weapons,
                                                                        [](const WeaponInfo &info) -> std::string {
                                                                            return info.name;
                                                                        });

                if (g_playerMgr == nullptr)
                    return;

                g_playerMgr->m_weaponId = closestMatch.id;

                toggle();
            } else if (nn::swkbd::IsDecideCancelButton(nullptr))
                toggle();
        }
    }

    bool WeaponChanger::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(WeaponChanger)
}
