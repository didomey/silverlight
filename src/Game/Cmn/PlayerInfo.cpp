#include "PlayerInfo.h"

namespace Cmn {
	void PlayerInfo::PlayerInfo::setPlayerName(short* nameBuf) {
		this->name[16] = 0x0;

		for (int i = 0; i < 16; i++) {
			this->name[i] = nameBuf[i];
		}

#ifdef SL_FEATURE
		this->name[SL_NAME_BUF] = 0x0;

		for (int i = 0; i < SL_NAME_BUF; i++) {
			if (nameBuf[i] == 0x0) {
				this->slName[i] = 0x0;
				break;
			}
			this->slName[i] = nameBuf[i];
		}
#endif
	}
}
