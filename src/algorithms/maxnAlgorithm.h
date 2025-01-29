#pragma once
#include "../map/grid.h"
#include "../entity/player.h"


class MaxnAlgorithm
{
public:

    // Constructor
    MaxnAlgorithm(Grid* grid);
    ~MaxnAlgorithm();

    //Methods
    bool isValidMove(int x, int y);


private:

};

