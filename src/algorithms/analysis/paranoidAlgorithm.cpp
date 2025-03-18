#include "paranoidAlgorithm.h"
#include <vector>
#include <limits>
#include <utility>
#include <iostream>
#include <cassert>

// Paranoïd is self explanatory, it maximise its score but fear others, considering they are all in team against him.
// Basically functions as a Maxn but taking other players into account.

ParanoidAlgorithm::ParanoidAlgorithm(MapManager* mapMan) : AlgorithmUtils(mapMan) {}

// TODO : IMPLEMENT TERRITORY AWARENESS

// Core Algorithme Paranoid
std::vector<int> ParanoidAlgorithm::paranoid(std::vector<std::shared_ptr<Player>> players, int depth, int currentPlayer) {
	int numPlayers = players.size();
	std::vector<int> scores(numPlayers + 1, 0);

	//Recur : end case -> return all scores for the current state
	if (depth == 0) {
		for (int i = 0; i < numPlayers; i++) {
			if (!players[i]->isPlayerDead()) {
				scores[players[i]->getId()] = this->evaluate(players[i]);
			}
		}
		return scores;
	}

	// Check if all players are dead
	bool allPlayersDead = true;
	for (const auto& player : players) {
		if (!player->isPlayerDead()) {
			allPlayersDead = false;
			break;
		}
	}
	if (allPlayersDead) {
		return std::vector<int>(numPlayers + 1, 0); // Return zero scores if all players are dead
	}

	// Declare needed values 
	std::shared_ptr<Player> player = players[currentPlayer];
	assert(player != nullptr); // Ensure player is not null
	int playerID = player->getId();

	// Skip dead players
	if (player->isPlayerDead()) {
		return this->paranoid(players, depth, (currentPlayer + 1) % numPlayers);
	}

	std::vector<int> bestScores(numPlayers + 1, INIT_VALUE); //Workaround to init numPlayer elems at a low int value, because int min changes to 

	bool hasValidMove = false;
	for (auto& [newX, newY] : this->getAvailableMoves(player)) {
		hasValidMove = true;

		//Save state and put wall behind player
		int oldX = player->getCoords().x;
		int oldY = player->getCoords().y;
		assert(this->getStoredMapMan() != nullptr); // Ensure map manager is not null
		this->getStoredMapMan()->setEntityAtCoords(player, newX, newY);

		//Recur on next plyr
		std::vector<int> scores = this->paranoid(players, depth - 1, (currentPlayer + 1) % numPlayers);

		//Restore
		this->getStoredMapMan()->setEntityAtCoords(player, oldX, oldY);
		this->getStoredMapMan()->restoreCell(newX, newY);

		//Update scores
		int myScore = scores[playerID];
		int sumOthers = 0;
		for (int i = 0; i < numPlayers; i++) {
			int pid = players[i]->getId();
			if (pid != playerID) {
				sumOthers += scores[pid];
			}
		}

		if (myScore - sumOthers > bestScores[playerID] - sumOthers) {
			if (bestScores[playerID] == INIT_VALUE) {
				bestScores = scores;
			} else {
				for (int i = 0; i < numPlayers; i++) {
					bestScores[i] += scores[i];
				}
			}
		}
	}

	// If no valid move, consider the player as dead for this branch
	if (!hasValidMove) {
		player->killPlayer();
		bestScores = this->paranoid(players, depth - 1, (currentPlayer + 1) % numPlayers);
		player->revive(); // Restore the player's state
	}

	return bestScores;
}
