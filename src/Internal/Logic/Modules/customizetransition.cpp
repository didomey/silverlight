//
// Created by tv on 04.11.23.
//
#include"customizetransition.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>
#include "Game/scene.h"
#include "Shared/strop.h"
#include "InputModule.h"
#include "Internal/silverlight.h"

void repl_handleSceneTransition(uint32_t* param_1, uint32_t id) {
	Modules::TransitionInput *transitionInput = silverlightInstance->m_moduleStates.getModule<Modules::TransitionInput>();

	SceneUtil::handleSceneTransition(param_1, transitionInput->transitionId);
}

namespace Modules {
	void TransitionInput::receivedEntry(const std::u16string &input) {
		TransitionInfo closestMatch = findClosestMatch<TransitionInfo>(u16string_to_string(input), transitions,
            [](const TransitionInfo &match) -> std::string {
            return match.name;
        });

		this->transitionId = closestMatch.id;
    }

	REGISTERVCLASS(TransitionInput)

    CustomizeTransition::CustomizeTransition() {
        this->patch = {
            {0x020828d8, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_handleSceneTransition, 0x020828d8), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) SceneUtil::handleSceneTransition, 0x020828d8))},
            {0x02082928, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_handleSceneTransition, 0x02082928), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) SceneUtil::handleSceneTransition, 0x02082928))},
            {0x02082978, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_handleSceneTransition, 0x02082978), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) SceneUtil::handleSceneTransition, 0x02082978))},
        };
    }

    bool CustomizeTransition::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(CustomizeTransition)
}
