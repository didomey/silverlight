#include "Game/Macros.h"

namespace nn {
	namespace nex {
		namespace InetAddress {
#pragma pack(push, 1)
			struct InetAddress {
			};
#pragma pack(pop)

			FUNCBIND(GetAddress, 02b61c60, void(*)(nn::nex::InetAddress::InetAddress* _this, uint32_t address, uint32_t unk))
			FUNCBIND(SetAddress, 02b62d24, void(*)(nn::nex::InetAddress::InetAddress* _this, uint32_t address))
		}
	}
}
