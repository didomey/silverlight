#include"rainmakerchaos.h"
#include "Game/Unk.h"
#include "Game/Unk3.h"

namespace Modules {
    void RainmakerChaos::start() {
    }

    void RainmakerChaos::stop() {
    }

    void RainmakerChaos::update(float deltaTime) {
		if (!g_unk || !g_unk3) return;

		CAFEINFO("ok 1");

		auto unk1 = g_unk->m_unk1;

		if (!unk1) return;

		CAFEINFO("ok 2");

		auto unk2 = unk1->m_unk1;

		if (!unk2) return;

		CAFEINFO("ok 3");

		auto unk3 = g_unk3->m_unk1;

		if (!unk3) return;

		CAFEINFO("ok 4");

		auto unk4 = unk3->m_unk1;

		if (!unk4) return;

		CAFEINFO("ok 5");

		for (uint32_t i = 0; i < 7; i++) {
			unk4->m_unk1 = 1;
			unk4->m_unk2 = 1;
			unk4->m_unk3 = i;
			unk4->m_unk4 = 1;
		}
    }

    bool RainmakerChaos::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(RainmakerChaos)
}
