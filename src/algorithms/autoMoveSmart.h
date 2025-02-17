#pragma once
#include "../map/grid.h"
#include "../entity/player.h"
#include "../entity/wall.h"
#include "../manager/mapManager.h"
#include "algorithmUtils.h"
#include <vector>

class AutoMoveSmart : public AlgorithmUtils {
public:
    // Constructor
    AutoMoveSmart(MapManager* mapMan);
    ~AutoMoveSmart() = default;

    //Methods
    std::pair<std::pair<int, int>, int> decideMove(std::shared_ptr<Player> players, int depth);

private:

};