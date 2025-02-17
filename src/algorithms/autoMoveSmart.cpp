#include "autoMoveSmart.h"
#include <iostream>
#include <vector>
#include <limits>

// This algorithm is a smart auto move algorithm
// It uses a scoring on the quality of the position at n=depth to decide the best move to make


AutoMoveSmart::AutoMoveSmart(MapManager* mapMan) : AlgorithmUtils(mapMan) {
}

// Auto moves algorithm
std::pair<std::pair<int, int>, int> AutoMoveSmart::decideMove(std::shared_ptr<Player> player, int depth) {
	std::pair<int, int> nextPos = { player->getCoords().x, player->getCoords().y}; //Init next pos at actual pos in case of no move possible
	int bestScore = -1;

	//Recur : end case -> return the score for the current placement
	if (depth == 0) {
		int score = this->evaluate(player);
		return {nextPos, score};
	}

	for (auto& [newX, newY] : this->getAvailableMoves(player)) {
		//Save state and move
		int oldX = player->getCoords().x;
		int oldY = player->getCoords().y;
		this->getStoredMapMan()->setEntityAtCoords(player, newX, newY);

		//Recur on the next position
		std::pair<std::pair<int, int>, int> res = this->decideMove(player, depth - 1);
		int score = res.second;

		//Restore
		this->getStoredMapMan()->setEntityAtCoords(player, oldX, oldY);
		this->getStoredMapMan()->restoreCell(newX, newY);

		if (score > bestScore) {
			bestScore = score;
			nextPos = {newX, newY};
		}
	}

	return {nextPos, bestScore};
}





