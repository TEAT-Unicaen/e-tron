#include "../map/grid.h"
#include "mapManager.h"
#include <iostream>

// Constructor
MapManager::MapManager(int line, int column)
	: grid(new Grid(line, column)) {
}

MapManager::~MapManager() {
}

// Methods
void MapManager::renderMap() {
	for (int i = 0; i < grid->getLine(); ++i) {
		for (int j = 0; j < grid->getColumn(); ++j) {
			Cell& cell = grid->getCell(i, j);
			std::cout << "Cell(" << i << "," << j << "): " << cell.getName() << "	";
		}
		std::cout << std::endl;
	}
}

// Setters
void MapManager::setGrid(Grid* grid) {
	this->grid = grid;
}

// Getters
Grid* MapManager::getGrid() {
	return grid;
}

