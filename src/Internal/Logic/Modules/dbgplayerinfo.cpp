#include"dbgplayerinfo.h"
#include "Shared/Core/Logging.h"
#include "Shared/Cafe/vpad.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include "Game/MainMgrBase.h"
#include "InputModule.h"
#include "Internal/silverlight.h"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "Game/DevLpUtil.h"
#include "Game/eui/MessageMgr.h"
#include "Game/Cui/MsgArg.h"
#include "Game/Cmn/DayChangeChecker.h"
#include "Game/Cui/MsgWindowPageHandler.h"
#include "Game/sead/SafeString.h"
#include "Game/BossUploadDataMaker.h"
#include "Game/VictoryLift.h"

static Game::Player::Player prevPlayer = {};

static glm::vec3 positionDeltaPeak = { 0.0, 0.0, 0.0 };

//FUNCBIND(getFixedEnlPlayerNum, 028af048, int32_t(*)(void))

void repl_tryMountSD(const char* path) {
	std::string pathStr = path;
	CAFEINFO("-[Lp]-");
	CAFEINFO(" -[Utl]-");
	CAFEINFO(" tryMountSD(const char* path) called");
	CAFEINFO(" path: \"" + pathStr + "\"");
	CAFEINFO("");
}

namespace Modules {
	void DbgPlayerInfoInput::receivedEntry(const std::u16string &input) {
		this->playerIdx = toUnsignedInt(input);
    }

	REGISTERVCLASS(DbgPlayerInfoInput)

    void DbgPlayerInfoUpdate::start() {
		//DbgPlayerInfoInput *dbgPlayerInfoInputModule = silverlightInstance->m_moduleStates.getModule<DbgPlayerInfoInput>();
		//Game::Player::Player* player = Game::Utl::getPerformerByIdx(dbgPlayerInfoInputModule->playerIdx);
		//prevPlayer = *player;
    }

    void DbgPlayerInfoUpdate::stop() {
    }

    void DbgPlayerInfoUpdate::update(float deltaTime) {
	}

    bool DbgPlayerInfoUpdate::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DbgPlayerInfoUpdate)

    DbgPlayerInfoPatch::DbgPlayerInfoPatch() {
		//this->patch = {{0x02869664, PatchElement(DynamicBranchReplacementSingle(BranchType::Branch, (void*) repl_tryMountSD, 0x02869664), "blr")}};
    }

    bool DbgPlayerInfoPatch::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DbgPlayerInfoPatch)

    void DbgPlayerInfoWrapper::start() {
		DbgPlayerInfoUpdate *dbgPlayerInfoUpdateModule = silverlightInstance->m_moduleStates.getModule<DbgPlayerInfoUpdate>();
		//DbgPlayerInfoPatch *dbgPlayerInfoPatchModule = silverlightInstance->m_moduleStates.getModule<DbgPlayerInfoPatch>();

		dbgPlayerInfoUpdateModule->m_enabled = true;
		//dbgPlayerInfoPatchModule->enablePatch();
    }

    void DbgPlayerInfoWrapper::stop() {
		DbgPlayerInfoUpdate *dbgPlayerInfoUpdateModule = silverlightInstance->m_moduleStates.getModule<DbgPlayerInfoUpdate>();
		//DbgPlayerInfoPatch *dbgPlayerInfoPatchModule = silverlightInstance->m_moduleStates.getModule<DbgPlayerInfoPatch>();

		dbgPlayerInfoUpdateModule->m_enabled = false;
		//dbgPlayerInfoPatchModule->disablePatch();
    }

    void DbgPlayerInfoWrapper::update(float deltaTime) {
	}

    bool DbgPlayerInfoWrapper::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(DbgPlayerInfoWrapper)
}
