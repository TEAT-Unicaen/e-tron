#include "MovingAlgorithmsManager.h"
#include <iostream>
#include <vector>
#include <limits>
#include <cassert>

MovingAlgorithmsManager::MovingAlgorithmsManager(MapManager* mapMan) : autoMoveSmart(mapMan), autoMoveSos(mapMan), autoMoveBFS(mapMan) {}

std::pair<std::pair<int, int>, int> MovingAlgorithmsManager::useAlgorithm(AlgoEnum algo, std::shared_ptr<Player> player, int depth, const std::vector<std::vector<double>>& W) {
	switch (algo) {
		case AlgoEnum::BFS:
			return autoMoveBFS.decideMoveBFS(player);
		case AlgoEnum::SOS:
			return autoMoveSos.decideMove(player, depth, W);
		default:
			return autoMoveSmart.decideMove(player, depth);
	}
}
