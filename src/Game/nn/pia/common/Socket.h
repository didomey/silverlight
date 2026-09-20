#include "Game/Macros.h"
#include "InetAddress.h"

namespace nn {
	namespace pia {
		namespace common {
			namespace Socket {
				struct Socket {
				};

				FUNCBIND(SendTo, 02c48f2c, int32_t(*)(nn::pia::common::Socket::Socket* _this, int32_t param_1, int32_t param_2, nn::pia::common::InetAddress::InetAddress* ipAddress, int32_t* param_4))
				FUNCBIND(RecvFrom, 02c48b50, int32_t(*)(nn::pia::common::Socket::Socket* _this, int32_t param_1, int32_t param_2, nn::pia::common::InetAddress::InetAddress* ipAddress, int32_t param_4, int32_t* param_5))
			}
		}
	}
}
