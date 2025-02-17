#include "../map/grid.h"
#include "../entity/wall.h"
#include "mapManager.h"
#include <iostream>
#include <memory>

// Constructor
MapManager::MapManager(int line, int column) noexcept
	: grid(new Grid(line, column)) {}

// Methods
void MapManager::renderMap() const noexcept {
	grid->renderGrid();
}

// Setters
void MapManager::setGrid(Grid* grid) noexcept {
	this->grid = grid;
}

// Getters
Grid* MapManager::getGrid() const noexcept {
	return grid;
}

bool MapManager::setEntityAtCoords(std::shared_ptr<GameEntity> ent, int x, int y) {
	if (x < 0 || x >= grid->getLine() || y < 0 || y >= grid->getColumn()) {
		return false;
	}
	ent->setCoords({ x, y });
	grid->setCell(grid->getCell(x, y), ent);
	return true;
}

bool MapManager::setEntityAtCoords(std::shared_ptr<GameEntity> ent, TCoords coords) {
	return setEntityAtCoords(ent, coords.x, coords.y);
}

void MapManager::placeWallAtCoords(Player * owner, int x, int y)  {
	this->setEntityAtCoords(std::shared_ptr<Wall>(new Wall("wall " + std::to_string(owner->getId()), { x,y }, owner->getColor(), owner)), {x,y});
}

void MapManager::restoreCell(int x, int y) noexcept {
	grid->initCell(x, y);
}