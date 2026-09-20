#include "Game/Macros.h"

namespace nn {
	namespace pia {
		namespace session {
			namespace Mesh {
				struct Mesh {};

				FUNCBIND(IsValidStationIndex, 02c8b284, bool(*)(nn::pia::session::Mesh::Mesh* _this, uint32_t stationIdx))
				FUNCBIND(UnfixDisconnectedId, 02c8b454, void(*)(nn::pia::session::Mesh::Mesh* _this, uint32_t stationIdx))

				GVARBIND(s_pMesh, 101e897c, nn::pia::session::Mesh::Mesh*)
			}
		}
	}
}
