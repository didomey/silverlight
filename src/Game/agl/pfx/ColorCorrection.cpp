#include <cstdint>
#include "ColorCorrection.h"

bool agl::pfx::ColorCorrection::ColorCorrection::enablePassHue() {
	return this->hue != 0.0;
}

void agl::pfx::ColorCorrection::ColorCorrection::setHue(float val) {
  	if (this->hue == val) return;

    this->hue = val;

    bool passHueEnabled = this->enablePassHue();
    uint32_t uVar2 = this->m_unk1;

    if ((uVar2 >> 2 & 1) != (uint32_t)passHueEnabled) {
		if (!passHueEnabled) {
			uVar2 = uVar2 & 0xfffffffb | 2;
		}
		else {
			uVar2 = uVar2 | 6;
		}
    }

    this->m_unk1 = uVar2 | 1;
}
