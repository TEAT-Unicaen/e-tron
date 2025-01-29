#pragma once
#include "../map/grid.h"
#include "../entity/player.h"


class MaxnAlgorithm {
public:
    // Constructor
    MaxnAlgorithm(Grid* grid) noexcept;
    ~MaxnAlgorithm() = default;

    //Methods
    bool isValidMove(int x, int y) const noexcept;

private:

};

