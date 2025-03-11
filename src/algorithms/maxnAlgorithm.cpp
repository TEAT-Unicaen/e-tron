#include "maxnAlgorithm.h"
#include <iostream>
#include <vector>
#include <limits>

// Maxn maximise its score, considering it is alone.
// Basically function as a Minimax but with multiple players.


MaxnAlgorithm::MaxnAlgorithm(MapManager* mapMan) : AlgorithmUtils(mapMan) {
}

// TODO : IMPLEMENT TERRITORY AWARENESS

// Core Algorithme Maxn
std::vector<int> MaxnAlgorithm::maxn(std::vector<std::shared_ptr<Player>> players, int depth, int currentPlayer) {
	int numPlayers = players.size();

    //Recur : end case -> return all scores for the current state
    if (depth == 0) {
		std::vector<int> scores(numPlayers + 1, 0);
		for (int i = 0; i < numPlayers; i++) {
			scores[players[i]->getId()] = this->evaluate(players[i]);
		}
		return scores;
    }

	std::shared_ptr<Player> player = players[currentPlayer];
	int playerId = player->getId();
	std::vector<int> bestScores(numPlayers + 1, INIT_VALUE); //Workaround to init numPlayer elems at minimum a low int value, not min int because of overlaps

    for (auto& [newX, newY] : this->getAvailableMoves(player)) {
		//Save state and move
		int oldX = player->getCoords().x;
		int oldY = player->getCoords().y;
		this->getStoredMapMan()->setEntityAtCoords(player, newX, newY);

        //Recur on next plyr
		std::vector<int> scores = this->maxn(players, depth - 1, (currentPlayer + 1) % numPlayers);

        //Restore
		this->getStoredMapMan()->setEntityAtCoords(player, oldX, oldY);
		this->getStoredMapMan()->restoreCell(newX, newY);

        //Update score if needed
		if (scores[playerId] > bestScores[playerId]) {
			// if its the first registred score, copy it, else increment it
			if (bestScores[playerId] == INIT_VALUE) {
				bestScores = scores;
			} else {
				for (int i = 0; i < numPlayers; i++) {
					bestScores[i] += scores[i];
				}
			}
		}
    }

    return bestScores;
}





