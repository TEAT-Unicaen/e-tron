#include "gameManager.h"


GameManager::GameManager(int line, int column)
	: mapManager(new MapManager(line, column)) {
}

GameManager::~GameManager() {
}

void GameManager::Start() {
	mapManager->renderMap();
}

void GameManager::setMapManager(MapManager* mapManager) {
	this->mapManager = mapManager;
}

MapManager* GameManager::getMapManager() {
	return mapManager;
}

bool GameManager::applyMove(GameEntity ent, TCoords coords) {
	Grid* grid = this->mapManager->getGrid();
	if (coords.x < 0 || coords.x >= grid->getLine() || coords.y < 0 || coords.y >= grid->getColumn()) {
		return false;
	}
	grid->setCell(grid->getCell(coords.x,coords.y), ent);
	return true;
}

