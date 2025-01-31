#include "maxnAlgorithm.h"
#include <iostream>
#include <vector>
#include <limits>

// Maxn maximise its score, considering it is alone.
// Basically function as a Minimax but with multiple players.


MaxnAlgorithm::MaxnAlgorithm(MapManager* mapMan) : AlgorithmUtils(mapMan) {
}

// Core Algorithme Maxn
std::vector<int> MaxnAlgorithm::maxn(std::vector<Player> players, int depth, int currentPlayer) {
	int numPlayers = players.size();

    //Recur : end case -> return all scores for the current state
    if (depth == 0) {
		std::vector<int> scores(numPlayers, 0);
		for (int i = 0; i < numPlayers; i++) {
			scores[i] = this->evaluate(players[i]);
		}
		return scores;
    }

	Player& player = players[currentPlayer];
	std::vector<int> bestScores(numPlayers, std::numeric_limits<int>::min()); //Workaround to init numPlayer elems at minimum int value (-2^63)

    for (auto [newX, newY] : this->getAvailableMoves(player)) {
		//Save state and move
		int oldX = player.getCoords().x;
		int oldY = player.getCoords().y;
		this->getStoredMapMan()->setEntityAtCoords(player, newX, newY);

        //Recur on next plyr
		std::vector<int> scores = this->maxn(players, depth - 1, (currentPlayer + 1) % numPlayers);

        //Restore
		this->getStoredMapMan()->setEntityAtCoords(player, oldX, oldY);
        
        //Update score if needed
		if (scores[currentPlayer] > bestScores[currentPlayer]) {
			bestScores = scores;
		}
    }

    return bestScores;
}





