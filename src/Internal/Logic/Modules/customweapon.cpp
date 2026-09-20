#include<Internal/Logic/modules.h>
#include<nn/swkbd.h>
#include "Internal/silverlight.h"
#include "customweapon.h"
#include "Shared/Cafe/swkbd.h"
#include <Game/weapons.h>
#include <Shared/strop.h>
#include<Game/MainMgr.h>
#include "Game/savedatavss.h"

static Weapon weapon = { 0, 0, 0, 0, 0 };

Weapon* customweapon_repl_getPlayerCustomWeaponSetId(int32_t *param_1, int32_t *param_2) {
    return &weapon;
}

namespace Modules {
	MainWeapon::MainWeapon() {
	}

    void MainWeapon::start() {
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

    void MainWeapon::stop() {
        nn::swkbd::DisappearInputForm();

        silverlightInstance->m_menuControl = true;
    }

    void MainWeapon::update(float deltaTime) {
        if (Cafe::Swkbd::update()) {
            if (nn::swkbd::IsDecideOkButton(nullptr)) {
                std::u16string str = nn::swkbd::GetInputFormString();

                std::string requestedWeapon = u16string_to_string(str);

				WeaponInfo &closestMatch = findClosestMatch<WeaponInfo>(requestedWeapon, weaponIds,
                    [](const WeaponInfo &info) -> std::string {
                    return info.name;
                });

				weapon.weaponId = closestMatch.id;

                toggle();
            } else if (nn::swkbd::IsDecideCancelButton(nullptr))
                toggle();
        }
    }

    bool MainWeapon::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(MainWeapon)
	
	SubWeapon::SubWeapon() {
	}

    void SubWeapon::start() {
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

    void SubWeapon::stop() {
        nn::swkbd::DisappearInputForm();

        silverlightInstance->m_menuControl = true;
    }

    void SubWeapon::update(float deltaTime) {
        if (Cafe::Swkbd::update()) {
            if (nn::swkbd::IsDecideOkButton(nullptr)) {
                std::u16string str = nn::swkbd::GetInputFormString();

                std::string requestedWeapon = u16string_to_string(str);

				WeaponInfo &closestMatch = findClosestMatch<WeaponInfo>(requestedWeapon, subWeaponIds,
                    [](const WeaponInfo &info) -> std::string {
                    return info.name;
                });

				weapon.subWeaponId = closestMatch.id;

                toggle();
            } else if (nn::swkbd::IsDecideCancelButton(nullptr))
                toggle();
        }
    }

    bool SubWeapon::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(SubWeapon)
	
	SpecialWeapon::SpecialWeapon() {
	}

    void SpecialWeapon::start() {
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

    void SpecialWeapon::stop() {
        nn::swkbd::DisappearInputForm();

        silverlightInstance->m_menuControl = true;
    }

    void SpecialWeapon::update(float deltaTime) {
        if (Cafe::Swkbd::update()) {
            if (nn::swkbd::IsDecideOkButton(nullptr)) {
                std::u16string str = nn::swkbd::GetInputFormString();

                std::string requestedWeapon = u16string_to_string(str);

				WeaponInfo &closestMatch = findClosestMatch<WeaponInfo>(requestedWeapon, specialWeaponIds,
                    [](const WeaponInfo &info) -> std::string {
                    return info.name;
                });

				weapon.specialWeaponId = closestMatch.id;

                toggle();
            } else if (nn::swkbd::IsDecideCancelButton(nullptr))
                toggle();
        }
    }

    bool SpecialWeapon::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(SpecialWeapon)

	CustomWeapon::CustomWeapon() {
        this->patch = {
		    {0x021a893c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) customweapon_repl_getPlayerCustomWeaponSetId, 0x021a893c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) getPlayerCustomWeaponSetId, 0x021a893c))},
            {0x021a936c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) customweapon_repl_getPlayerCustomWeaponSetId, 0x021a936c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) getPlayerCustomWeaponSetId, 0x021a936c))},
        };
    }

    bool CustomWeapon::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(CustomWeapon)
}
