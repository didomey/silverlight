namespace Game {
	namespace RequestPaintArg {
		enum class PaintCommandType {
			MainWeaponPaint=-1,
			SubWeaponPaint=0
		};

		struct RequestPaintArg { /* PlaceHolder Class Structure */
			int field0_0x0;
			int wallSpread;
			glm::vec3 paintPos;
			float paintAmount;
			glm::vec2 dropLeftoverPaint;
			int paintTeam;
			float _paintPos;
			float field10_0x28;
			int32_t field11_0x2c;
			uint8_t field12_0x30;
			uint8_t field13_0x31;
			uint8_t field14_0x32;
			uint8_t field15_0x33;
			PaintCommandType paintCommandType;
			uint8_t field17_0x38;
		};

		ENSURE_OFFSET(RequestPaintArg, paintPos, 0x8);
		ENSURE_OFFSET(RequestPaintArg, paintTeam, 0x20);

		FUNCBIND(ctor, 02456d34, int32_t(*)(int32_t _this, double param_1, double param_2, int32_t param_3, int32_t param_4, int32_t param_5, int32_t param_6, int32_t param_7, int32_t param_8, int32_t param_9, byte param_10, int32_t param_11, int32_t param_12))
	}
}
