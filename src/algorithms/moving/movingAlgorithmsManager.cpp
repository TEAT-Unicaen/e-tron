#include "MovingAlgorithmsManager.h"
#include <iostream>
#include <vector>
#include <limits>
#include <cassert>

MovingAlgorithmsManager::MovingAlgorithmsManager(MapManager* mapMan) : autoMoveSmart(mapMan), autoMoveSos(mapMan) {}

std::pair<std::pair<int, int>, int> MovingAlgorithmsManager::useAlgorithm(bool isSosOriented, std::shared_ptr<Player> player, int depth, const std::vector<std::vector<double>>& W) {
	if (isSosOriented) {
		return autoMoveSos.decideMove(player, depth, W);
	}
	return autoMoveSmart.decideMove(player, depth);
}
