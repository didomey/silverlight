#pragma once

#include<Internal/Logic/modules.h>
#include<nn/swkbd.h>
#include "Internal/silverlight.h"
#include "Internal/Logic/UpdateModule.h"

namespace Modules {
    class SearchForBytesInput : public Modules::UpdateModule {
    VCLASS(SearchForBytesInput, ESC({&Modules::UpdateModule::classInfo, nullptr}))

    private:
        SearchForBytesInput();

        void start() override;

        void stop() override;

        void update(float deltaTime) override;

        bool isCheatModule() override;

		friend class SearchForBytes;

	public:
		std::vector<uint32_t> locatedLocations;
    };

    class SearchForBytes : public Modules::UpdateModule {
    VCLASS(SearchForBytes, ESC({&Modules::UpdateModule::classInfo, nullptr}))

    private:
		SearchForBytes();

		void start() override;

		void stop() override;

        void render(float deltaTime) override;

        bool isCheatModule() override;
    };

    class BreakpointInput : public Modules::UpdateModule {
    VCLASS(BreakpointInput, ESC({&Modules::UpdateModule::classInfo, nullptr}))

    private:
        BreakpointInput();

        void start() override;

        void stop() override;

        void update(float deltaTime) override;

        bool isCheatModule() override;

		friend class Breakpoint;

	public:
		std::vector<uint32_t> locatedLocations;
    };
}
