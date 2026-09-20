//
// Created by tv on 04.11.23.
//
#include"anonymizer.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include "antitelemetry.h"
#include "namechanger.h"
#include "zeropaint.h"
#include "customweapon.h"
#include "disablevisiblegear.h"
#include "Game/savedatavss.h"

Weapon *anonymizer_repl_getPlayerCustomWeaponSetId(int32_t *param_1, int32_t *param_2) {
    static Weapon *weapon = getPlayerCustomWeaponSetId(param_1, param_2);

    weapon->turfInked = 0;

    return weapon;
}

namespace Modules {
    AnonymizerPatch::AnonymizerPatch() {
        this->patch = {
                // Spoof the level
                {0x020f45dc, PatchElement("li r3, 0x0",
                                          DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) 0x021aeac8,
                                                                         0x020f45dc))},
                {0x021a943c, PatchElement("li r3, 0x0",
                                          DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) 0x021aeac8,
                                                                         0x021a943c))},
                // Spoof the level exp
                {0x020f45e8, PatchElement("li r3, 0x0",
                                          DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) 0x021aea7c,
                                                                         0x020f45e8))},

                // Spoof the rank
                {0x020f7fc4, PatchElement("li r3, 0x0",
                                          DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) 0x021aeb08,
                                                                         0x020f7fc4))},
                {0x020f7eec, PatchElement("li r3, 0x0",
                                          DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) 0x021aeb08,
                                                                         0x020f7eec))},
                {0x021a9450, PatchElement("li r3, 0x0",
                                          DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) 0x021aeb08,
                                                                         0x021a9450))},
                {0x024e20fc, PatchElement("li r3, 0x0",
                                          DynamicBranchReplacementSingle(BranchType::BranchLink, (void *) 0x021aeb08,
                                                                         0x024e20fc))},

                // Spoof gear
                // {0x021a93cc, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) anonymizer_repl_getCommonPlayerGearId, 0x021a93cc), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) getCommonPlayerGearId, 0x021a93cc))},

                // Spoof weapon
                {0x021a893c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink,
                                                                         (void *) anonymizer_repl_getPlayerCustomWeaponSetId,
                                                                         0x021a893c),
                                          DynamicBranchReplacementSingle(BranchType::BranchLink,
                                                                         (void *) getPlayerCustomWeaponSetId,
                                                                         0x021a893c))},
                //{0x021a936c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) anonymizer_repl_getPlayerCustomWeaponSetId, 0x021a936c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) getPlayerCustomWeaponSetId, 0x021a936c))},
        };
    }

    bool AnonymizerPatch::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(AnonymizerPatch)

    void AnonymizerUpdate::start() {
    }

    void AnonymizerUpdate::stop() {
        uint32_t ptr = *((uint32_t *) 0x101E80A4);

        if (0x10600000 < ptr &&
            ptr < 0x1D000000) {

            //emplace string 4 characters into the players name
            char *text = (char *) (ptr + 0x8C);

            memcpy(text, m_oldname.data(), m_oldname.size() + 1);
        }


    }

    void AnonymizerUpdate::update(float deltaTime) {

        AntiTelemetry *antiTelemetryModule = silverlightInstance->m_moduleStates.getModule<AntiTelemetry>();
        antiTelemetryModule->enablePatch();

        ZeroPaint *zeroPaintModule = silverlightInstance->m_moduleStates.getModule<ZeroPaint>();
        zeroPaintModule->m_enabled = true;

        DisableVisibleGear *disableVisibleGearModule = silverlightInstance->m_moduleStates.getModule<DisableVisibleGear>();
        disableVisibleGearModule->enablePatch();

        CustomWeapon *disableCustomWeaponModule = silverlightInstance->m_moduleStates.getModule<CustomWeapon>();
        disableCustomWeaponModule->disablePatch();

        // Spoof name
        uint32_t ptr = *((uint32_t *) 0x101E80A4);

        if (0x10600000 < ptr &&
            ptr < 0x1D000000) {

            //emplace string 4 characters into the players name
            char *text = (char *) (ptr + 0x8C);

            m_oldname = text;

            static char16_t emptyString[] = u"               ";

            memcpy(text, emptyString, 32);
        }
    }

    bool AnonymizerUpdate::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(AnonymizerUpdate)

	void AnonymizerWrapper::start() {
		AnonymizerUpdate *anonymizerUpdateModule = silverlightInstance->m_moduleStates.getModule<AnonymizerUpdate>();
		AnonymizerPatch *anonymizerPatchModule = silverlightInstance->m_moduleStates.getModule<AnonymizerPatch>();

		anonymizerUpdateModule->m_enabled = true;
		anonymizerPatchModule->enablePatch();
    }

    void AnonymizerWrapper::stop() {
		AnonymizerUpdate *anonymizerUpdateModule = silverlightInstance->m_moduleStates.getModule<AnonymizerUpdate>();
		AnonymizerPatch *anonymizerPatchModule = silverlightInstance->m_moduleStates.getModule<AnonymizerPatch>();

		anonymizerUpdateModule->m_enabled = false;
		anonymizerPatchModule->disablePatch();
	}

    void AnonymizerWrapper::update(float deltaTime) {
    }

    bool AnonymizerWrapper::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(AnonymizerWrapper)

}
