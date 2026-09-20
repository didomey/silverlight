#include"photoshoot.h"
#include "InputModule.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>
#include "Internal/silverlight.h"
#include "Game/CameraAccessor.h"
#include "Game/Player.h"
#include "Shared/Cafe/vpad.h"
#include "switchscene.h"
#include "Shared/strop.h"
#include <unordered_map>
#include "Game/Cmn/PlayerInfo.h"
#include "Game/sead/LookAtCamera.h"
#include "Game/sead/Matrix34.h"
#include <glm/glm.hpp>
#include <unordered_set>
#include "photographmode.h"
#include "freecam.h"

/*

   	general option command structure: set [player index] [option string] [value]
	example option command: set 1 gender 1
   	general option command structure: set [action string] [variadic action arguments]
	example action command: action tp 1 1

*/

using CommandCallback = bool (*)(Modules::PhotoshootCommandInput&, std::string);

bool tryRunCommandSet(Modules::PhotoshootCommandInput& photoshootInput, std::string command) {
	size_t seperatorPos = command.find(' ');
    if (seperatorPos == std::string::npos) {
		photoshootInput.error = "No arguments provided to command.";
		return false;
	}
	std::optional<int> playerIdxOptional = stringToInt(command.substr(0, seperatorPos));

	if (!playerIdxOptional.has_value()) {
		photoshootInput.error = "Invalid player index given.";
		return false;
	}
	int playerIdx = playerIdxOptional.value();
	command = command.substr(seperatorPos + 1, command.length() - seperatorPos + 1);

	seperatorPos = command.find(' ');
    if (seperatorPos == std::string::npos) {
		photoshootInput.error = "Option not provided to set.";
		return false;
	}
	std::string option = command.substr(0, seperatorPos);
	command = command.substr(seperatorPos + 1, command.length() - seperatorPos + 1);

	std::optional<int> valueOptional = stringToInt(command);

	std::unordered_set<std::string> intOptions = {"gender", "main", "fullmain", "hat", "shoes", "clothe"};

	if (intOptions.find(option) != intOptions.end()) {
		if (!valueOptional.has_value()) {
			photoshootInput.error = "Invalid value given.";
			return false;
		}
	}

	std::string value = command;

	std::vector<Game::Player::Player*> players = Game::Utl::getAllPlayers();

	playerIdx--;
	if (playerIdx >= players.size() || playerIdx < 0) {
		photoshootInput.error = "Invalid player index given.";
		return false;
	}

	Game::Player::Player* player = players[playerIdx];
	if (!player) {
		photoshootInput.error = "Player is NULL.";
		return false;
	}
	if (!player->info) {
		photoshootInput.error = "Player info is NULL.";
		return false;
	}

	Cmn::PlayerInfo::PlayerInfo& info = photoshootInput.infos[playerIdx];

	if (option == "gender") { info.gender = stringToInt(value).value(); }
	else if (option == "hat") { info.hat.gearId = stringToInt(value).value(); }
	else if (option == "clothe") { info.clothe.gearId = stringToInt(value).value(); }
	else if (option == "shoes") { info.shoes.gearId = stringToInt(value).value(); }
	else if (option == "name") { Cmn::PlayerInfo::setPlayerName(&photoshootInput.infos[playerIdx], static_cast<void*>(stringToShortArray(value).data())); }
	else if (option == "main") { info.weaponId = stringToInt(value).value(); }
	else if (option == "fullmain") { info.fullWeaponId = stringToInt(value).value(); }
	else {
		photoshootInput.error = "Invalid option given.";
		return false;
	}

	photoshootInput.infosInitialized[playerIdx] = true;

	return true;
}

bool tryRunCommandAction(Modules::PhotoshootCommandInput& photoshootInput, std::string command) {
	size_t seperatorPos = command.find(' ');
    if (seperatorPos == std::string::npos) {
		photoshootInput.error = "No arguments provided to command.";
		return false;
	}
	std::optional<int> playerIdxOptional = stringToInt(command.substr(0, seperatorPos));

	if (!playerIdxOptional.has_value()) {
		photoshootInput.error = "Invalid player index given.";
		return false;
	}
	int playerIdx = playerIdxOptional.value();
	command = command.substr(seperatorPos + 1, command.length() - seperatorPos + 1);

	seperatorPos = command.find(' ');
    if (seperatorPos == std::string::npos) {
		photoshootInput.error = "Option not provided to action.";
		return false;
	}
	std::string option = command.substr(0, seperatorPos);
	command = command.substr(seperatorPos + 1, command.length() - seperatorPos + 1);

	std::optional<int> valueOptional = stringToInt(command);

	if (!valueOptional.has_value()) {
		photoshootInput.error = "Invalid value given.";
		return false;
	}

	int value = valueOptional.value();

	std::vector<Game::Player::Player*> players = Game::Utl::getAllPlayers();

	playerIdx--;
	if (playerIdx >= players.size() || playerIdx < 0) {
		photoshootInput.error = "Invalid player index given.";
		return false;
	}

	Game::Player::Player* player = players[playerIdx];
	if (!player) {
		photoshootInput.error = "Player is NULL.";
		return false;
	}

	if (option == "anim") {
		if (!player->playerMotion) {
			photoshootInput.error = "Player motion is NULL.";
			return false;
		}

		if (value > 0x50) {
			Game::PlayerMotion::startEventAnim(player->playerMotion, &value, 0.0, 1.0);
		} else {
			Game::PlayerMotion::FUN_026c7884(player->playerMotion, &value);
		}
	} else if (option == "tp") {
		if (value >= players.size()) {
			photoshootInput.error = "Invalid target player given.";
			return false;
		}

		value--;

		Game::Player::Player* targetPlayer = players[value];

		player->position = targetPlayer->position;
	} else {
		photoshootInput.error = "Invalid option given.";
		return false;
	}

	return true;
}

const std::unordered_map<std::string, CommandCallback> commands = {
	{ "set", tryRunCommandSet },
	{ "action", tryRunCommandAction }
};

void repl_dbgSetRandomValue(Cmn::PlayerInfo::PlayerInfo* _this, int32_t unk) {
	if (!_this) return;

	Modules::PhotoshootCommandInput *photoshootCommandInputModule = silverlightInstance->m_moduleStates.getModule<Modules::PhotoshootCommandInput>();

	CAFEINFO("Index: " + std::to_string(_this->index));

	if (photoshootCommandInputModule->infosInitialized[_this->index]) {
		_this->gender = photoshootCommandInputModule->infos[_this->index].gender;
		_this->hat.gearId = photoshootCommandInputModule->infos[_this->index].hat.gearId;
		_this->clothe.gearId = photoshootCommandInputModule->infos[_this->index].clothe.gearId;
		_this->shoes.gearId = photoshootCommandInputModule->infos[_this->index].shoes.gearId;
		_this->weaponId = photoshootCommandInputModule->infos[_this->index].weaponId;
		_this->fullWeaponId = photoshootCommandInputModule->infos[_this->index].fullWeaponId;
		for (int i = 0; i < sizeof(_this->name) / sizeof(_this->name[0]); i++) {
			_this->name[i] = photoshootCommandInputModule->infos[_this->index].name[i];
		}
	}
}

static glm::mat3x4 cam = {};
static bool firstTime = true;

void repl_doUpdateMatrix(sead::LookAtCamera::LookAtCamera* _this, glm::mat3x4* res) {
	if (firstTime) {
		cam = *res;
		firstTime = false;
	}

    VPADStatus status = {};
    VPADReadError err;

    VPADRead(VPAD_CHAN_0, &status, 1, &err);

    Inputs *inputs = (Inputs *) &status.hold;

	float movementSpeed = 0.02;

	if (inputs->StickLEmulationUp || inputs->StickLEmulationDown) {
		cam[0][1] += movementSpeed;
	}

	*res = cam;
}

namespace Modules {
	PhotoshootCommandInput::PhotoshootCommandInput() {
	}

	bool PhotoshootCommandInput::isCheatModule() {
		return false;
	}

	void PhotoshootCommandInput::receivedEntry(const std::u16string &input) {
        std::string commandInput = u16string_to_string(input);
		trim(commandInput);

		size_t commandSeperatorPos = commandInput.find(' ');

    	if (commandSeperatorPos == std::string::npos) {
			this->error = "No command given.";
			return;
		}

		std::string command = commandInput.substr(0, commandSeperatorPos);

		if (commands.find(command) == commands.end()) {
			this->error = "Command given is invalid.";
			return;
		}

		std::string restCommand = commandInput.substr(commandSeperatorPos + 1, commandInput.length() - commandSeperatorPos + 1);

		CommandCallback commandCallback = commands.at(command);

		if (commandCallback(*this, restCommand)) {
			this->error = "";
		}
    }

    REGISTERVCLASS(PhotoshootCommandInput)

    PhotoshootPatch::PhotoshootPatch() {
        this->patch = {
			/*
            {0x020777b8, PatchElement("blr", "lis r12, 0x1001")},
			// Causes some weapons to break
			//{0x02634fac, PatchElement("li r31, 0", "li r31, 1")}

            {0x026421ec, PatchElement("li r3, 0", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02634f54, 0x026421ec))},
            {0x02659e24, PatchElement("li r3, 0", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02634f54, 0x02659e24))},
			*/

            {0x021a7c8c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_dbgSetRandomValue, 0x021a7c8c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Cmn::PlayerInfo::dbgSetRandomValue, 0x021a7c8c))},
            {0x021a7de0, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_dbgSetRandomValue, 0x021a7de0), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Cmn::PlayerInfo::dbgSetRandomValue, 0x021a7de0))},
			{0x021a7e04, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_dbgSetRandomValue, 0x021a7e04), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Cmn::PlayerInfo::dbgSetRandomValue, 0x021a7e04))},
            {0x021a7e94, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_dbgSetRandomValue, 0x021a7e94), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Cmn::PlayerInfo::dbgSetRandomValue, 0x021a7e94))},
            {0x021a7eb8, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_dbgSetRandomValue, 0x021a7eb8), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Cmn::PlayerInfo::dbgSetRandomValue, 0x021a7eb8))},
            {0x021a8088, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_dbgSetRandomValue, 0x021a8088), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Cmn::PlayerInfo::dbgSetRandomValue, 0x021a8088))},
            {0x021a80ac, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_dbgSetRandomValue, 0x021a80ac), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Cmn::PlayerInfo::dbgSetRandomValue, 0x021a80ac))},
            {0x021a8144, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_dbgSetRandomValue, 0x021a8144), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Cmn::PlayerInfo::dbgSetRandomValue, 0x021a8144))},

            //{0x020148f0, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_doUpdateMatrix, 0x020148f0), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) sead::LookAtCamera::doUpdateMatrix, 0x020148f0))},
        };
    }

    bool PhotoshootPatch::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(PhotoshootPatch)

	void PhotoshootUpdate::onEnable() {
		firstTime = true;
	}

	bool PhotoshootUpdate::requireRenderFocus() {
		return true;
	}

    void PhotoshootUpdate::onDisable() {
    }

    void PhotoshootUpdate::update(float deltaTime) {
		static Inputs lastHeld = {};

        VPADStatus status = {};
        VPADReadError err;

        VPADRead(VPAD_CHAN_0, &status, 1, &err);

        Inputs *inputs = (Inputs *) &status.hold;

        if (inputs->ButtonLeft && !lastHeld.ButtonLeft) {
			if (this->selectedPlayerIdx > 0) {
            	this->selectedPlayerIdx--;
			}
        } else if (inputs->ButtonRight && !lastHeld.ButtonRight) {
			if (this->selectedPlayerIdx < Game::Utl::getAllPlayers().size() - 1) {
            	this->selectedPlayerIdx++;
			}
        }

		if (inputs->ButtonPlus && !lastHeld.ButtonPlus) {
			CAFEINFO("called");

			if (Game::CameraAccessor::sInstance) {
				if (Game::CameraAccessor::sInstance->cameraControlState == 0) {
					Game::CameraAccessor::sInstance->cameraControlState = 1;
				} else {
					Game::CameraAccessor::sInstance->cameraControlState = 0;
				}
			}
		}

		if (inputs->ButtonMinus && !lastHeld.ButtonMinus) {
			FreecamWrapper *freecamModule = silverlightInstance->m_moduleStates.getModule<FreecamWrapper>();
			freecamModule->toggle();
		}
		
		if (inputs->ButtonR && !lastHeld.ButtonR) {
			PhotoshootCommandInput *photoshootCommandInputModule = silverlightInstance->m_moduleStates.getModule<PhotoshootCommandInput>();
			photoshootCommandInputModule->toggle();
		}

		if (inputs->ButtonL && !lastHeld.ButtonL) {
			this->renderingEnabled ^= true;
		}

		if (inputs->ButtonL && inputs->ButtonDown && (!lastHeld.ButtonL || !lastHeld.ButtonDown)) {
			CAFEINFO("pressed");
			Modules::PhotoshootCommandInput *photoshootCommandInputModule = silverlightInstance->m_moduleStates.getModule<Modules::PhotoshootCommandInput>();
			if (tryRunCommandAction(*photoshootCommandInputModule, "action " + std::to_string(Game::Utl::getPlayerIdx(Game::Player::localInstance) + 1) + " tp " + std::to_string(this->selectedPlayerIdx + 1))) {
				photoshootCommandInputModule->error = "";
			}
			return;
		}

		if (inputs->ButtonDown && !lastHeld.ButtonDown) {
			g_nextSceneId = 43;
			switchScene(g_nextSceneId);
		}
		if (inputs->ButtonUp && !lastHeld.ButtonUp) {
			PhotographModePatch *photographModule = silverlightInstance->m_moduleStates.getModule<PhotographModePatch>();
			photographModule->toggle();
		}

		std::vector<Game::Player::Player*> players = Game::Utl::getAllPlayers();

		if (this->selectedPlayerIdx >= players.size()) {
			this->selectedPlayerIdx--;
			return;
		}

		lastHeld = *inputs;
    }

    bool PhotoshootUpdate::isCheatModule() {
        return false;
    }

	void PhotoshootUpdate::render(float deltaTime) {
		if (!this->renderingEnabled) return;

		std::vector<Game::Player::Player*> players = Game::Utl::getAllPlayers();
		uint32_t& selectedPlayerIdx = this->selectedPlayerIdx;

		if (selectedPlayerIdx >= players.size()) {
			return;
		}

		Game::Player::Player* selectedPlayer = players[selectedPlayerIdx];
		if (!selectedPlayer) return;
		if (!selectedPlayer->info) return;

		std::string selectedPlayerName = {};

		for (short byte : selectedPlayer->info->name) {
			selectedPlayerName.push_back(static_cast<char>(byte));
		}

		int x = -400;

		int i = 300;
		std::string text = "Selected Player: " + selectedPlayerName + " (" + std::to_string(selectedPlayerIdx) + ")";
		silverlightInstance->m_renderer.setTextCursor({x, i});
		silverlightInstance->m_renderer.drawText(text);
		i -= 25;
		text = "[DPAD-Right / DPAD-Left] Select Player";
		silverlightInstance->m_renderer.setTextCursor({x, i});
		silverlightInstance->m_renderer.drawText(text);
		i -= 25;
		text = "[L] Hide Menu";
		silverlightInstance->m_renderer.setTextCursor({x, i});
        silverlightInstance->m_renderer.drawText(text);
		i -= 25;
		text = "[R] Set Player Option Value";
		silverlightInstance->m_renderer.setTextCursor({x, i});
        silverlightInstance->m_renderer.drawText(text);
		i -= 25;
		text = "[+] Lock/Unlock Camera Position";
		silverlightInstance->m_renderer.setTextCursor({x, i});
        silverlightInstance->m_renderer.drawText(text);
		i -= 25;
		text = "[-] Toggle Freecam";
		silverlightInstance->m_renderer.setTextCursor({x, i});
        silverlightInstance->m_renderer.drawText(text);
		i -= 25;
		text = "[DPAD-Down] Reload Scene";
		silverlightInstance->m_renderer.setTextCursor({x, i});
        silverlightInstance->m_renderer.drawText(text);
		i -= 25;
		text = "[DPAD-Up] Disable Photograph Mode";
		silverlightInstance->m_renderer.setTextCursor({x, i});
        silverlightInstance->m_renderer.drawText(text);
		i -= 25;
		text = "[L + DPAD-Up] Teleport Player";
		silverlightInstance->m_renderer.setTextCursor({x, i});
        silverlightInstance->m_renderer.drawText(text);

		PhotoshootCommandInput *photoshootCommandInputModule = silverlightInstance->m_moduleStates.getModule<PhotoshootCommandInput>();

		if (!photoshootCommandInputModule->error.empty()) {
			i -= 25;
			text = photoshootCommandInputModule->error;
			silverlightInstance->m_renderer.setTextCursor({-400, i});
        	silverlightInstance->m_renderer.drawText(text);
		}
	}

    REGISTERVCLASS(PhotoshootUpdate)

	void PhotoshootWrapper::onEnable() {
    }

    void PhotoshootWrapper::onDisable() {
    }

    void PhotoshootWrapper::update(float deltaTime) {
    }

    bool PhotoshootWrapper::isCheatModule() {
        return false;
    }

	std::vector<const char*> PhotoshootWrapper::incompatibleModules() {
		return {"PauseMenuAlwaysUsable"};
	}

	std::vector<const char*> PhotoshootWrapper::requiredModules() {
		return {"PhotoshootUpdate", "PhotoshootPatch"};
	}

    REGISTERVCLASS(PhotoshootWrapper)
}
