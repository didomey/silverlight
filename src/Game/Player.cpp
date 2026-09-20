#include "MainMgrBase.h"
#include "Player.h"

namespace Game {
	namespace Utl {
		std::vector<Game::Player::Player*> getAllPlayers() {
			Game::Player::Player** players = Game::MainMgrBase::sInstance->playerMgr->factories->playerFactoryIdx->playerActors;
			uint32_t playerCount = Game::MainMgrBase::sInstance->playerMgr->factories->playerFactoryIdx->maxPlayerCount;

			if (playerCount == 0) return {};

			std::vector<Game::Player::Player*> result = {};

			for (int i = 0; i < playerCount; i++) {
				Game::Player::Player* player = players[i];
				if (!player) continue;
				result.push_back(player);
			}

			return result;
		}

		std::vector<Game::Player::Player*> getAllEnemies() {
			if (!Game::Player::localInstance) return {};

			std::vector<Game::Player::Player*> players = Game::Utl::getAllPlayers();
			std::vector<Game::Player::Player*> enemies = {};

			for (const auto player : players) {
				if (player->teamId != Game::Player::localInstance->teamId) {
					enemies.push_back(player);
				}
			}

			return enemies;
		}

		std::vector<Game::Player::Player*> getAllTeammates() {
			if (!Game::Player::localInstance) return {};

			std::vector<Game::Player::Player*> players = Game::Utl::getAllPlayers();
			std::vector<Game::Player::Player*> teammates = {};

			for (const auto player : players) {
				if (player->teamId == Game::Player::localInstance->teamId) {
					teammates.push_back(player);
				}
			}

			return teammates;
		}

		size_t getAliveTeammateCnt() {
			if (!Game::Player::localInstance) return {};
			
			std::vector<Game::Player::Player*> teammates = Game::Utl::getAllTeammates();

			size_t aliveTeammateCnt = 0;

			for (const auto teammate : teammates) {
				if (teammate->isAlive()) {
					aliveTeammateCnt++;
				}
			}

			return aliveTeammateCnt;
		}

		uint32_t getPlayerIdx(Game::Player::Player* player) {
			Game::Player::Player** players = Game::MainMgrBase::sInstance->playerMgr->factories->playerFactoryIdx->playerActors;
			uint32_t playerCount = Game::MainMgrBase::sInstance->playerMgr->factories->playerFactoryIdx->maxPlayerCount;

			uint32_t localPlayerIdx;

			for (uint32_t i = 0; i < playerCount; i++) {
				Game::Player::Player* curPlayer = players[i];

				if (!curPlayer) continue;

				if (curPlayer == player) {
					localPlayerIdx = i;
					break;
				}
			}

			return localPlayerIdx;
		}
	}

	bool Player::Player::isAlive() {
		if (this->deathUnk1 < 1 && this->deathUnk2 < 1 && this->deathFrm < 1) {
			return true;
		}

		return false;
	}

	bool Player::Player::isInSuperjump() {
		return this->superjumpState > 0;
	}

	bool Player::Player::isControlledPlayer() {
		return this == Game::Player::localInstance;
	}
}
