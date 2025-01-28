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

bool MapManager::applyMove(GameEntity ent, int x, int y) {
	if (x < 0 || x >= grid->getLine() || y < 0 || y >= grid->getColumn()) {
		return false;
	}
	grid->setCell(grid->getCell(x, y), ent);
	return true;
}

bool MapManager::applyMove(GameEntity ent, TCoords coords) {
	return applyMove(ent, coords.x, coords.y);
}