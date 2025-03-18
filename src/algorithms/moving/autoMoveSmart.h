#pragma once

#include "../algorithmUtils.h"
#include "./IMovingAlgorithm.h"
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