//
// Created by tv on 26.11.23.
//
//02175f60

#include<Internal/Logic/modules.h>
#include <nn/swkbd/swkbd_cpp.h>
#include "Internal/silverlight.h"
#include"mapforce.h"
#include "Shared/Cafe/swkbd.h"

using GetMapIdFunc = uint32_t(*)();
static GetMapIdFunc getMapId = (GetMapIdFunc) 0x02174b84;

static uint32_t g_mapForceVal = 0;

uint32_t getMapIdReplacement() {
    getMapId();
    return silverlightInstance->m_moduleStates.getModule<Modules::MapForce>()->m_mapId;
}

namespace Modules {
    MapForce::MapForce() {
        patch = {
                {0x02175f60,
                 PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) getMapIdReplacement,
                                                             0x02175f60),
                              DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) getMapId, 0x02175f60)),
                },
        };
		this->disablePatch();
    }

    bool MapForce::isCheatModule() {
        return false;
    }


    bool MapForceInput::isCheatModule() {
        return false;
    }

    void MapForceInput::start() {
        silverlightInstance->m_menuControl = false;

        nn::swkbd::AppearArg appearArg;
        appearArg.keyboardArg.configArg.languageType = nn::swkbd::LanguageType::English;
        appearArg.inputFormArg.hintText = u"Name";
        if (!nn::swkbd::AppearInputForm(appearArg)) {
            CAFEERRORSHOW("Unable to open keyboard")

            return;
        }
    }

    void MapForceInput::stop() {

        nn::swkbd::DisappearInputForm();

        silverlightInstance->m_menuControl = true;
    }

    void MapForceInput::update(float deltaTime) {
        VPADStatus vpadStatus;
        VPADRead(VPAD_CHAN_0, &vpadStatus, 1, nullptr);


        if (Cafe::Swkbd::update()) {
            if (nn::swkbd::IsDecideOkButton(nullptr)) {
                std::u16string text = nn::swkbd::GetInputFormString();

                if (isUnsignedInt(text)) {
                    silverlightInstance->m_moduleStates.getModule<MapForce>()->m_mapId = toUnsignedInt(text);
                    CAFEINFO("Setting map id to: " +
                             std::to_string(silverlightInstance->m_moduleStates.getModule<MapForce>()->m_mapId))
                } else
                    CAFEERRORSHOW("Input is not an unsigned int!")

                toggle();
            } else if (nn::swkbd::IsDecideCancelButton(nullptr)) {
                toggle();
            }
        }
    }


    REGISTERVCLASS(MapForce)
    REGISTERVCLASS(MapForceInput)
}
