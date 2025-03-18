#pragma once
#include "../algorithmUtils.h"
#include <vector>

class AutoMoveSos : public AlgorithmUtils {
public:
    // Constructor
    AutoMoveSos(MapManager* mapMan);
    ~AutoMoveSos() = default;

    //Methods
    std::pair<std::pair<int, int>, int> decideMove(std::shared_ptr<Player> player, int depth, const std::vector<std::vector<double>>& W);

private:

    int const INIT_VALUE = -100000;

};
