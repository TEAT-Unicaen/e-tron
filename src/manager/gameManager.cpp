#include "gameManager.h"

GameManager::GameManager(int line, int column)
	: mapManager(new MapManager(line, column)), running(false) {
}

GameManager::~GameManager() {
	if (this->running) {
		this->stop();
	}
}

void GameManager::draw() {
	mapManager->renderMap();
}

void GameManager::setMapManager(MapManager* mapManager) {
	this->mapManager = mapManager;
}

MapManager* GameManager::getMapManager() {
	return mapManager;
}

void GameManager::stop() {
	running = false;
	if (gameThread.joinable()) {
		gameThread.join();
	}
}

void GameManager::threadLoop() {
	running = true;
	while (running) {
		SLEEP(1);
		std::cout << "Loop" << std::endl;
	}
}

void GameManager::loop() {
	if (gameThread.joinable()) {
		gameThread.join(); 
	}
	gameThread = std::thread(&GameManager::threadLoop, this);
}