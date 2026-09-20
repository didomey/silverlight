//
// Created by tv on 04.11.23.
//

#pragma once

#include<glm/vec3.hpp>
#include "Internal/Logic/UpdateModule.h"

#include "InputModule.h"

namespace Modules {
	class DbgPlayerInfoInput : public InputModule {
    VCLASS(DbgPlayerInfoInput, ESC({&InputModule::classInfo, nullptr}))
		void receivedEntry(const std::u16string &input) override;
		
		uint32_t playerIdx;
    };

    class DbgPlayerInfoUpdate : public UpdateModule {
    VCLASS(DbgPlayerInfoUpdate, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
	};

	class DbgPlayerInfoPatch : public PatchModule {
	VCLASS(DbgPlayerInfoPatch, ESC({&UpdateModule::classInfo, nullptr}))
	public:
		DbgPlayerInfoPatch();

		bool isCheatModule() override;
    };

    class DbgPlayerInfoWrapper : public UpdateModule {
    VCLASS(DbgPlayerInfoWrapper, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        void start() override;

        void stop() override;

        bool isCheatModule() override;

    public:
        void update(float deltaTime) override;
	};
}
