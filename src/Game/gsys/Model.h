#include "Game/Macros.h"

namespace gsys {
	namespace Model {
		struct Model {};

		FUNCBIND(requestDraw, 02a4c36c, void(*)(gsys::Model::Model* _this))
		FUNCBIND(setVisible, 02a4c544, void(*)(gsys::Model::Model* _this, bool isVisible, int32_t unk))
	}
}
