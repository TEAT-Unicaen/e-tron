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
	grid->renderGrid();
}

// Setters
void MapManager::setGrid(Grid* grid) {
	this->grid = grid;
}

// Getters
Grid* MapManager::getGrid() {
	return grid;
}

