#pragma once

#include "autoMoveSmart.h"
#include "autoMoveSos.h"
#include "autoMoveBFS.h"

class MovingAlgorithmsManager  {
public:

    enum class AlgoEnum {
        SMART,
		SOS,
		BFS
    };


    MovingAlgorithmsManager(MapManager* mapMan);
    ~MovingAlgorithmsManager() = default;

    std::pair<std::pair<int, int>, int> useAlgorithm(AlgoEnum algo, std::shared_ptr<Player> player, int depth, int numP);

private:

	AutoMoveSmart autoMoveSmart;
	AutoMoveSos autoMoveSos;
    AutoMoveBFS autoMoveBFS;
};
