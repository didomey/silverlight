//
// Created by tv on 26.11.23.
//

#pragma once

#include<Internal/Logic/modules.h>

namespace Modules {
	class MapForce : public Modules::PatchModule {
	VCLASS(MapForce, ESC({&Modules::PatchModule::classInfo, nullptr}))

	public:
		MapForce();

		bool isCheatModule() override;

		uint32_t m_mapId;

	};

	class MapForceInput : public Modules::UpdateModule {
	VCLASS(MapForceInput, ESC({&Modules::UpdateModule::classInfo, nullptr}))
	private:

		void start() override;

		void stop() override;

		void update(float deltaTime) override;

		bool isCheatModule() override;

	};
}
