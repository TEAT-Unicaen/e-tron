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

