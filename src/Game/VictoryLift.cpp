#include "VictoryLift.h"
#include "Player.h"

namespace Game {
	namespace VictoryLift {
		static TowerState getTowerState() {
			std::vector<Game::Player::Player*> players = Game::Utl::getAllPlayers();

			size_t alphaPlayers = 0;
			size_t bravoPlayers = 0;

			for (const auto player : players) {
				if (player->isOnTower && player->teamId == 1) {
					alphaPlayers++;
				}

				if (player->isOnTower && player->teamId == 2) {
					bravoPlayers++;
				}
			}

			if (alphaPlayers > 0 && bravoPlayers == 0) return TowerState::ControlledByAlpha;
			if (bravoPlayers > 0 && alphaPlayers == 0) return TowerState::ControlledByBravo;

			return TowerState::Uncontrolled;
		}
	}
}
