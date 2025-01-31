#pragma once
#include "../map/grid.h"
#include "../entity/player.h"
#include "../entity/wall.h"
#include "../manager/mapManager.h"
#include "algorithmUtils.h"
#include <vector>

class MaxnAlgorithm : public AlgorithmUtils {
public:
    // Constructor
    MaxnAlgorithm(MapManager* mapMan);
    ~MaxnAlgorithm() = default;

    //Methods
	std::vector<int> maxn(std::vector<Player> players, int depth, int currentPlayer);

private:

};

