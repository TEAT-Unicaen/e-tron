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
	ent.setCoords({ x, y });
	grid->setCell(grid->getCell(x, y), ent);
	return true;
}

bool MapManager::applyMove(GameEntity ent, TCoords coords) {
	return applyMove(ent, coords.x, coords.y);
}

bool MapManager::swapCell(TCoords coords1, TCoords coords2) {
	if (coords1.x < 0 || coords1.x >= grid->getLine() || coords1.y< 0 || coords1.y >= grid->getColumn()) {
		return false;
	}
	if (coords2.x < 0 || coords2.x >= grid->getLine() || coords2.y < 0 || coords2.y >= grid->getColumn()) {
		return false;
	}

	GameEntity ent1 = grid->getCell(coords1.x, coords1.y).getEntity();
	GameEntity ent2 = grid->getCell(coords2.x, coords2.y).getEntity();
	
	if (ent1) {
		this->applyMove(ent1, coords2);
	}
	if (ent2) {
		this->applyMove(ent2, coords1);
	}

	return true;
}