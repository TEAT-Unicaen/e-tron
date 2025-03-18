#pragma once

#include "autoMoveSmart.h"
#include "autoMoveSos.h"

class MovingAlgorithmsManager  {
public:
    // Constructor
    MovingAlgorithmsManager(MapManager* mapMan);
    ~MovingAlgorithmsManager() = default;

    //Methods
    std::pair<std::pair<int, int>, int> useAlgorithm(bool isSosOriented, std::shared_ptr<Player> player, int depth, const std::vector<std::vector<double>>& W);

private:

	AutoMoveSmart autoMoveSmart;
	AutoMoveSos autoMoveSos;
        
};
