#include "gameManager.h"

GameManager::GameManager(int line, int column) noexcept
	: mapManager(new MapManager(line, column)), running(false) {}

GameManager::~GameManager() {
	if (this->running) {
		this->stop();
	}
}

void GameManager::draw() const noexcept {
	this->mapManager->renderMap();
}

void GameManager::setMapManager(MapManager* mapManager) noexcept {
	this->mapManager = mapManager;
}

MapManager* GameManager::getMapManager() const noexcept {
	return this->mapManager;
}

void GameManager::stop() {
	this->running = false;
	if (this->gameThread.joinable()) {
		this->gameThread.join();
	} else {
		throw ETRON_EXCEPT("GameManager is running but the gameThread don't run");
	}
}

void GameManager::addUpdatable(IUpdatable* updatable) noexcept {
	this->updatables.push_back(updatable);
}

std::vector<IUpdatable*> GameManager::getUpdatables() const noexcept {
	return this->updatables;
}

void GameManager::threadLoop() {
	running = true;
	while (running) {
		SLEEP(1);

		for (auto* updatable : this->updatables) {
			if (updatable) {
				updatable->update();
			} else {
				throw ETRON_EXCEPT("Invalid updatable, there is a null here wtf");
			}
		}

		std::cout << "\033[2J\033[H";
		this->draw();
	}
}

void GameManager::loop() {
	if (this->gameThread.joinable()) {
		this->gameThread.join();
	}
	this->gameThread = std::thread(&GameManager::threadLoop, this);
	if (!this->gameThread.joinable()) {
		throw ETRON_EXCEPT("GameThread is not lauch");
	}
}

Player GameManager::createPlayer(std::string name, int i, int y, int uniqueInt) {
	/* NEED TO FIX THIS
	if (this->getMapManager()->getGrid()->getCell(i, y).getEntity()) {
		throw ETRON_EXCEPT("Cell already taken");
	}
	*/
	Player entity = Player(name, {i,y}, uniqueInt, uniqueInt);
	this->getMapManager()->setEntityAtCoords(entity, i, y);
	return entity;
}

MaxnAlgorithm GameManager::callMaxn() {
	return MaxnAlgorithm(this->getMapManager());
}

ParanoidAlgorithm GameManager::callParanoid() {
	return ParanoidAlgorithm(this->getMapManager());
}