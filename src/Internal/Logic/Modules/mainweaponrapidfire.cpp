//
// Created by tv on 04.11.23.
//
#include"mainweaponrapidfire.h"
#include <Game/Globals/Unk.h>
#include "Shared/Cafe/vpad.h"
#include "Game/Unk2.h"

namespace Modules {

    void MainWeaponRapidFire::start() {
    }

    void MainWeaponRapidFire::stop() {
    }

    void MainWeaponRapidFire::update(float deltaTime) {
		VPADStatus status = {};
        VPADReadError err;

        VPADRead(VPAD_CHAN_0, &status, 1, &err);

        Inputs *inputs = (Inputs *) &status.hold;

		if (inputs->ButtonL) {
			auto unk1 = getUnk2();

			if (!unk1) return;

			auto unk2 = unk1->m_unk1;

			if (!unk2) return;

			auto unk3 = unk2->m_unk1;

			if (!unk3) return;

			// Shooter / Blaster
			unk3->m_unk1 = 0x005E0000;
			unk3->m_unk2 = 0x005E0000;
			unk3->m_unk10 = 0x0;

			// Charger
			unk3->m_unk3 = 0x3F800000;

			// Roller
			unk3->m_unk4 = 0x10;
			unk3->m_unk5 = 0x1;

			// Slosher
			unk3->m_unk6 = 0x1;

			// Splatling (Spinner)
			unk3->m_unk7 = 0x87;
			unk3->m_unk8 = 0x87;
			unk3->m_unk9 = 0x3F800000;
		}
    }

    bool MainWeaponRapidFire::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(MainWeaponRapidFire)
}
