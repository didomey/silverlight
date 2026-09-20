//
// Created by tv on 03.11.23.
//

#pragma once

#include<cstdint>
#include<optional>
#include <glm/vec3.hpp>
#include "Macros.h"
#include<array>

namespace CameraMgr {
	namespace RivalSquadController {
		#pragma pack(push, 1)
		struct RivalSquadController {
			std::array<char, 0x40> unk1;
			float* cameraMtx;
		};

		ENSURE_OFFSET(RivalSquadController, cameraMtx, 0x40);
		#pragma pack(pop)

		FUNCBIND(getCameraMtx, 0200df2c, glm::vec3*(*)(RivalSquadController* _this))
		FUNCBIND(getCameraDir, 0200df34, glm::vec3*(*)(RivalSquadController* _this))
	}

	#pragma pack(push, 1)
	struct Camera1 {
		std::array<char, 0x58> unk1;
		uint32_t cameraState;

		std::array<char, 0x1c> unk2;
		RivalSquadController::RivalSquadController* rivalSquadController;
	};

	ENSURE_OFFSET(Camera1, rivalSquadController, 0x78);

	struct CameraUnk {
		std::array<char, 0x18> unk1;
		Camera1* camera1;
	};

	ENSURE_OFFSET(CameraUnk, camera1, 0x18);

	#pragma pack(pop)

	GVARBIND(sInstance, 101dcdb4, CameraUnk *)
}
