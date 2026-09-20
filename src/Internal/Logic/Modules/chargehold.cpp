#include"chargehold.h"
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
#include "Game/PlayerWeapon.h"

static uint32_t heldChargeFrm = 0;

void repl_setChargeRate(Cmn::PlayerWeapon::PlayerWeapon* _this, float amount) {
	if (amount == 0.0) {
		if (heldChargeFrm != 0) {
			if (!Game::Player::localInstance->isSwimming_) {
				heldChargeFrm = 0;
			}
		}
	}

	Cmn::PlayerWeapon::setChargeRate(_this, amount);
}

namespace Modules {
    void ChargeHoldUpdate::start() {
    }

    void ChargeHoldUpdate::stop() {
    }

    void ChargeHoldUpdate::update(float deltaTime) {
		VPADStatus status = {};
        VPADReadError err;
        VPADRead(VPAD_CHAN_0, &status, 1, &err);

        Inputs *inputs = (Inputs *) &status.hold;

		if (Game::Player::localInstance->playerInkAction->chargeFrm > 0) {
			if (Game::Player::localInstance->playerInkAction->chargeFrm == 1 && heldChargeFrm > 0) {
				CAFEINFO("Charge restored (" + std::to_string(heldChargeFrm) + ")");
				Game::Player::localInstance->playerInkAction->chargeFrm = heldChargeFrm >= 10 ? heldChargeFrm - 10 : 0;
				heldChargeFrm = 0;
			} else {
				heldChargeFrm = Game::Player::localInstance->playerInkAction->chargeFrm;
			}
		} else {
			if (!inputs->ButtonZR) {
				heldChargeFrm = 0;
				return;
			}
		}
    }

    bool ChargeHoldUpdate::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(ChargeHoldUpdate)

	ChargeHoldPatch::ChargeHoldPatch() {
		/*
		this->patch = {
            {0x100ef7d0, PatchElement((void*) repl_setChargeRate, (void*) Cmn::PlayerWeapon::setChargeRate)},
            {0x100efd54, PatchElement((void*) repl_setChargeRate, (void*) Cmn::PlayerWeapon::setChargeRate)},
            {0x100f029c, PatchElement((void*) repl_setChargeRate, (void*) Cmn::PlayerWeapon::setChargeRate)},
            {0x100f08c4, PatchElement((void*) repl_setChargeRate, (void*) Cmn::PlayerWeapon::setChargeRate)},
            {0x100f10ec, PatchElement((void*) repl_setChargeRate, (void*) Cmn::PlayerWeapon::setChargeRate)},
            {0x100efaac, PatchElement((void*) repl_setChargeRate, (void*) Cmn::PlayerWeapon::setChargeRate)},
            {0x100efff8, PatchElement((void*) repl_setChargeRate, (void*) Cmn::PlayerWeapon::setChargeRate)},
            {0x100f0594, PatchElement((void*) repl_setChargeRate, (void*) Cmn::PlayerWeapon::setChargeRate)},
            {0x100f0e48, PatchElement((void*) repl_setChargeRate, (void*) Cmn::PlayerWeapon::setChargeRate)},
        };
		*/
    }

    bool ChargeHoldPatch::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(ChargeHoldPatch)


	void ChargeHoldWrapper::start() {
        ChargeHoldUpdate *chargeHoldUpdateModule = silverlightInstance->m_moduleStates.getModule<ChargeHoldUpdate>();
        ChargeHoldPatch *chargeHoldPatchModule = silverlightInstance->m_moduleStates.getModule<ChargeHoldPatch>();

        chargeHoldUpdateModule->m_enabled = true;
        chargeHoldPatchModule->enablePatch();
    }

    void ChargeHoldWrapper::stop() {
        ChargeHoldUpdate *chargeHoldUpdateModule = silverlightInstance->m_moduleStates.getModule<ChargeHoldUpdate>();
        ChargeHoldPatch *chargeHoldPatchModule = silverlightInstance->m_moduleStates.getModule<ChargeHoldPatch>();

        chargeHoldUpdateModule->m_enabled = false;
        chargeHoldPatchModule->disablePatch();
    }

    void ChargeHoldWrapper::update(float deltaTime) {
    }

    bool ChargeHoldWrapper::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(ChargeHoldWrapper)

}
