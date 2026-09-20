//
// Created by tv on 04.11.23.
//
#include"infinitetime.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include "Game/Macros.h"

void repl_LAB_0274c268() {
	__asm__(
		R"(
			lis 5, 0x00ff
			ori 5, 5, 0xffff
		)"
		B(0x0274, 0xc26c)
	);
}

namespace Modules {
    InfiniteTime::InfiniteTime() {
        this->patch = {
                {0x0274c268, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_LAB_0274c268, 0x0274c268), "li r5, 0x4650")},
        };
    }

    bool InfiniteTime::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(InfiniteTime)
}
