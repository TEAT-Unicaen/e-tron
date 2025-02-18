#include "paranoidAlgorithm.h"
#include <vector>
#include <limits>
#include <utility>

// Paranoïd is self explanatory, it maximise its score but fear others, considering they are all in team against him.
// Basically functions as a Maxn but taking other players into account.

ParanoidAlgorithm::ParanoidAlgorithm(MapManager* mapMan) : AlgorithmUtils(mapMan) {
}

// TODO : IMPLEMENT TERRITORY AWARENESS


// Core Algorithme Paranoid
std::vector<int> ParanoidAlgorithm::paranoid(std::vector<std::shared_ptr<Player>> players, int depth, int currentPlayer) {
	int numPlayers = players.size();
	std::vector<int> scores(numPlayers, 0);

	//Recur : end case -> return all scores for the current state
	if (depth == 0) {
		for (int i = 0; i < numPlayers; i++) {
			scores[i] = this->evaluate(players[i]);
		}
		return scores;
	}

	std::shared_ptr<Player> player = players[currentPlayer];
	std::vector<int> bestScores(numPlayers, std::numeric_limits<int>::min()); //Workaround to init numPlayer elems at minimum int value (-2^63)
	std::vector<std::pair<int, int>> moves = this->getAvailableMoves(player);

	if (moves.empty()) { // Plyr eliminated -> applying penalty
		scores[currentPlayer] = -1000;
		return scores;
	}

	for (auto& [newX, newY] : moves) {
		//Save state and put wall behind player
		int oldX = player->getCoords().x;
		int oldY = player->getCoords().y;
		this->getStoredMapMan()->setEntityAtCoords(player, newX, newY);

		//Recur on next plyr
		std::vector<int> scores = this->paranoid(players, depth - 1, (currentPlayer + 1) % numPlayers);

		//Restore
		this->getStoredMapMan()->setEntityAtCoords(player, oldX, oldY);
		this->getStoredMapMan()->restoreCell(newX, newY);

		//Update score if needed
		int myScore = scores[currentPlayer];
		int sumOthers = 0;
		for (int i = 0; i < numPlayers; i++) {
			if (i != currentPlayer) {
				sumOthers += scores[i];
			}
		}

		if (myScore - sumOthers > bestScores[currentPlayer] - sumOthers) {
			bestScores = scores;
		}
	}
	return bestScores;
}
