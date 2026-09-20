#include"freecam.h"
#include "Shared/Core/Logging.h"
#include "Shared/Cafe/vpad.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<vpad/input.h>
#include<glm/mat3x3.hpp>
#include<Game/Assembler/ppcAssembler.h>
#include "Internal/silverlight.h"
#include "Game/CameraUnk.h"
#include "Game/Player.h"
#include "futurefly.h"

static glm::vec3 pos = { 93.0, 75.0, 198.0 };

glm::vec3* repl_getCameraMtx(CameraMgr::RivalSquadController::RivalSquadController* _this) {
	return &pos;
}

void repl_calcPosAt(Game::PlayerBehindCamera::PlayerBehindCamera* _this) {
	glm::vec3 origPos = Game::Player::localInstance->position;
	Game::Player::localInstance->position = pos;
	Game::PlayerBehindCamera::calcPosAt(_this);
	Game::Player::localInstance->position = origPos;
}

void repl_calcBehindPosAt(Game::PlayerBehindCamera::PlayerBehindCamera *_this, double param_1, int32_t *param_2, glm::vec3 *param_3, glm::vec3 *param_4, uint32_t *param_5) {
	glm::vec3 origPos = Game::Player::localInstance->position;
	Game::Player::localInstance->position = pos;
	Game::PlayerBehindCamera::calcBehindPosAt(_this, param_1, param_2, param_3, param_4, param_5);
	Game::Player::localInstance->position = origPos;
}

double getPlayerTransparency(Game::Player::Player* player) {
	if (player == Game::Player::localInstance) {
		return 0.0;
	} else {
		return Game::Player::getPlayerTransparency(player);
	}
}

static glm::vec3 dirpos = { 0.0158911, 0.999589, -0.0238678 };

namespace Modules {
    void FreecamUpdate::start() {
		this->origPlayerPos = Game::Player::localInstance->position;
		g_playerMgr->m_hex4E4Unk = 0xFFFFFFF;
    }

    void FreecamUpdate::stop() {
		g_playerMgr->m_hex4E4Unk = 0x0;
    }

    void FreecamUpdate::update(float deltaTime) {
		VPADStatus status = {};
        VPADReadError err;

        VPADRead(VPAD_CHAN_0, &status, 1, &err);

        Inputs *inputs = (Inputs *) &status.hold;

        pos.x += status.leftStick.x * deltaTime * 200;
        pos.z += status.leftStick.y * deltaTime * 200;
        pos.y += status.rightStick.y * deltaTime * 200;

		Game::Player::localInstance->playerBehindCamera->forwardCamera.x = pos.x;
		Game::Player::localInstance->playerBehindCamera->upCamera.y = pos.y;
    }

    bool FreecamUpdate::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(FreecamUpdate)

    FreecamPatch::FreecamPatch() {
		this->patchLineBranch(0x0265a158, BranchType::BranchLink, (void*) getPlayerTransparency);
		this->patchLineBranch(0x0265a664, BranchType::BranchLink, (void*) getPlayerTransparency);

        //this->patch = {
                //{0x020146b8, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_getCameraMtx, 0x020146b8), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) CameraMgr::RivalSquadController::getCameraMtx, 0x020146b8))},
                //{0x026621e8, PatchElement("blr", "stwu r1, -0x1e8(r1)")},
                //{0x02668434, PatchElement("blr", "stwu r1, -0x80(r1)")},
                //{0x026655d4, PatchElement("blr", "stwu r1, -0xe0(r1)")},

                //{0x02668d20, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_calcPosAt, 0x02668d20), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::PlayerBehindCamera::calcPosAt, 0x02668d20))},
                //{0x0265fbec, PatchElement("blr", "mflr r0")},
        //};
    }

    bool FreecamPatch::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(FreecamPatch)

    void FreecamWrapper::start() {
		FreecamUpdate *freecamUpdateModule = silverlightInstance->m_moduleStates.getModule<FreecamUpdate>();
		FreecamPatch *freecamPatchModule = silverlightInstance->m_moduleStates.getModule<FreecamPatch>();
		FutureFly *futureflyModule = silverlightInstance->m_moduleStates.getModule<FutureFly>();

		freecamUpdateModule->enable();
		freecamPatchModule->enablePatch();
		futureflyModule->enable();
    }

    void FreecamWrapper::stop() {
		FreecamUpdate *freecamUpdateModule = silverlightInstance->m_moduleStates.getModule<FreecamUpdate>();
		FreecamPatch *freecamPatchModule = silverlightInstance->m_moduleStates.getModule<FreecamPatch>();
		FutureFly *futureflyModule = silverlightInstance->m_moduleStates.getModule<FutureFly>();

		freecamUpdateModule->disable();
		freecamPatchModule->disablePatch();
		futureflyModule->disable();
    }

    void FreecamWrapper::update(float deltaTime) {
    }

    bool FreecamWrapper::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(FreecamWrapper)
}
