#include "Game/Macros.h"
#include <array>

#pragma once

namespace agl {
	namespace pfx {
		namespace ColorCorrection {
#pragma pack(push, 1)
			struct ColorCorrection {
				std::array<char, 0x1c8> unk1;
				float hue;
				std::array<char, 0x11CC> unk2;
				uint32_t m_unk1;

				bool enablePassHue();
				void setHue(float val);
			};
#pragma pack(pop)

			FUNCBIND(ColorCorrectionCtor, 02a08a60, void(*)(agl::pfx::ColorCorrection::ColorCorrection* _this))
			FUNCBIND(setHue, 02a0a278, void(*)(float val, agl::pfx::ColorCorrection::ColorCorrection* _this))


			static agl::pfx::ColorCorrection::ColorCorrection* instance = nullptr;
		}
	}
}
