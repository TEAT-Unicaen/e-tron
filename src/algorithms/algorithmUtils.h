#pragma once
#include "../map/grid.h"
#include "../entity/player.h"
#include "../entity/wall.h"
#include "../manager/mapManager.h"
#include <vector>

class AlgorithmUtils {
public:
    // Constructor
    AlgorithmUtils(MapManager* mapMan);
    ~AlgorithmUtils() = default;

    //Methods
    bool isAValidMove(int x, int y);
    int evaluate(Player player);
    std::vector<std::pair<int, int>> getAvailableMoves(Player player);
	MapManager* getStoredMapMan();

private:

};