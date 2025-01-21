#include <iostream>
#include <cassert>
#include "../../map/grid.h"
#include "test_map.h"

void testGrid() {
    try {
        std::cout << "Create grid & draw each line :\n" << std::endl;
        Grid grid(3, 3);

        assert(grid.getLine() == 3);
        assert(grid.getColumn() == 3);

        std::cout << "Grid size: " << grid.getLine() << " x " << grid.getColumn() << std::endl;

        for (int i = 0; i < grid.getLine(); ++i) {
            for (int j = 0; j < grid.getColumn(); ++j) {
                Cell& cell = grid.getCell(i, j);
                std::cout << "Cell(" << i << "," << j << "): " << cell.getName() << std::endl;
            }
        }

        std::cout << "\nInvalid cell positions test :" << std::endl;
        try {
            grid.getCell(-1, 0);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }

        try {
            grid.getCell(0, 5);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }

    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

/*
int main() {
    testGrid();
    return 0;
}
*/