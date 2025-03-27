#include "MovingAlgorithmsManager.h"
#include <iostream>
#include <vector>
#include <limits>
#include <cassert>

#include "../../utils/affinitiesMatrixGenerator.h"


MovingAlgorithmsManager::MovingAlgorithmsManager(MapManager* mapMan) : autoMoveSmart(mapMan), autoMoveSos(mapMan), autoMoveBFS(mapMan) {}

std::pair<std::pair<int, int>, int> MovingAlgorithmsManager::useAlgorithm(AlgoEnum algo, std::shared_ptr<Player> player, int depth, int numP) {
	switch (algo) {
		case AlgoEnum::BFS:
			return autoMoveBFS.decideMoveBFS(player, depth);
		case AlgoEnum::SOS:
			return autoMoveSos.decideMove(player, depth, AffinitiesMatrixGenerator::generateRandomAffinities(numP));
		default:
			return autoMoveSmart.decideMove(player, depth);
	}
}
