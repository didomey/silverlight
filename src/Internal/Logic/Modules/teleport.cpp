#include <glm/vec3.hpp>
#include "Game/MainMgr.h"
#include "Internal/silverlight.h"

glm::vec3 teleportPlayerPosition = {};
glm::vec3 teleportPlayerMoveRotation = {};
glm::vec3 teleportPlayerUnk = {};

namespace Modules {
	void setTeleportPos() {
		teleportPlayerPosition = Game::PlayerMgr::sInstance->m_player1Position;
		teleportPlayerMoveRotation = Game::PlayerMgr::sInstance->m_playerBehindCamera->m_playerMoveRotation;
		teleportPlayerUnk = Game::PlayerMgr::sInstance->m_playerBehindCamera->m_unk1->m_Hex23CUnk;
	}

	void goToTeleportPos() {
		if (silverlightInstance->m_currentlyInPublicMatch) {
			return;
		}

		Game::PlayerMgr::sInstance->m_player1Position = teleportPlayerPosition;
		Game::PlayerMgr::sInstance->m_playerBehindCamera->m_playerMoveRotation = teleportPlayerMoveRotation;
		Game::PlayerMgr::sInstance->m_playerBehindCamera->m_unk1->m_Hex23CUnk = teleportPlayerUnk;
	}
}
