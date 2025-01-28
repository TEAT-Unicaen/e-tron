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

void GameManager::addUpdatable(IUpdatable* updatable) {
	this->updatables.push_back(updatable);
}

std::vector<IUpdatable*> GameManager::getUpdatables() {
	return this->updatables;
}

void GameManager::threadLoop() {
	running = true;
	while (running) {
		SLEEP(1);

		this->getMapManager()->swapCell({ 0,0 }, { 1,1 });

		for (auto* updatable : this->updatables) {
			if (updatable) {
				updatable->update();
			}
			else {
				throw std::runtime_error("Invalid updatable, there is a null here wtf");
			}
		}

		std::cout << "\033[2J\033[H";
		this->draw();
	}
}

void GameManager::loop() {
	if (gameThread.joinable()) {
		gameThread.join(); 
	}
	gameThread = std::thread(&GameManager::threadLoop, this);
}

void GameManager::debugEntity() {
	GameEntity entity = GameEntity("test", {0,0}, 0);
	this->getMapManager()->setEntityAtCoords(entity, 0, 0);
}