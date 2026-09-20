#include "Game/Unk4.h"

namespace Modules {
	void pauseGame() {
		if (!g_unk4) return;

		if (g_unk4->m_unk1 == 0)
			g_unk4->m_unk1 = 1;
		else
			g_unk4->m_unk1 = 0;
	}
}
