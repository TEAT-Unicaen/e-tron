#pragma once

#include "../algorithmUtils.h"
#include <vector>

class MaxnAlgorithm : public AlgorithmUtils {
public:
    // Constructor
    MaxnAlgorithm(MapManager* mapMan);
    ~MaxnAlgorithm() = default;

    //Methods
	std::vector<int> maxn(std::vector<std::shared_ptr<Player>> players, int depth, int currentPlayer);

private:

	int const INIT_VALUE = -100000;

};

