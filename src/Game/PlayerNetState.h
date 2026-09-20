#pragma once

#include "Game/Macros.h"

namespace Game {
	namespace PlayerNetState {
		struct PlayerNetState {
			float field0_0x0;
			int8_t field1_0x4;
			int8_t field2_0x5;
			short field3_0x6;
			float field4_0x8;
			float field5_0xc;
			float field6_0x10;
			float field7_0x14;
			char field8_0x18;
			int8_t field9_0x19;
			int8_t field10_0x1a;
			int8_t field11_0x1b;
			int32_t field12_0x1c;
			int32_t field13_0x20;
			int32_t field14_0x24;
			int8_t field15_0x28;
			int8_t field16_0x29;
			short field17_0x2a;
			float field18_0x2c;
			float field19_0x30;
			int32_t field20_0x34;
			int32_t field21_0x38;
			int32_t field22_0x3c;
			int32_t field23_0x40;
			int32_t field24_0x44;
			int32_t field25_0x48;
			int field26_0x4c;
			float field27_0x50;
			int field28_0x54;
			int field29_0x58;
			int32_t field30_0x5c;
			int32_t field31_0x60;
			int8_t field32_0x64;
			int8_t field33_0x66;
			int8_t field34_0x67;
			uint32_t field35_0x68;
			uint32_t field36_0x6c;
			int32_t field37_0x70;
		};

		GVARBIND(data, 100e9d8c, Game::PlayerNetState::PlayerNetState *);
	}
}
