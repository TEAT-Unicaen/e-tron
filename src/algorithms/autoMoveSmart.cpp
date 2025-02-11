#include "autoMoveSmart.h"
#include <iostream>
#include <vector>
#include <limits>

// This algorithm is a smart auto move algorithm
// It uses a scoring on the quality of the position at n=depth to decide the best move to make


AutoMoveSmart::AutoMoveSmart(MapManager* mapMan) : AlgorithmUtils(mapMan) {
}

// Auto moves algorithm
std::pair<std::pair<int, int>, int> AutoMoveSmart::decideMove(Player player, int depth) {
	int numPlayers = players.size();
	std::pair<int, int> nextPos = {0, 0} //Init next pos at actual pos in case of no move possible
	int bestScore = 0;

	//Recur : end case -> return the score for the current placement
	if (depth == 0) {
		return this->evaluate(player);
	}


	for (auto [newX, newY] : this->getAvailableMoves(player)) {
		//Save state and move
		int oldX = player.getCoords().x;
		int oldY = player.getCoords().y;
		this->getStoredMapMan()->setEntityAtCoords(player, newX, newY);

		//Recur on next plyr
		std::pair<std::pair<int, int>, int> nextPos, score = this->maxn(player, depth - 1);

		//Restore
		this->getStoredMapMan()->setEntityAtCoords(player, oldX, oldY);

		if score > bestScore {
			bestScore = score;
			nextPos = {newX, newY};
		}
	}

	return nextPos, bestScore;
}





