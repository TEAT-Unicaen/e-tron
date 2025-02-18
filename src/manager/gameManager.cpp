#include "gameManager.h"
#include "../entity/player.h"
#include "../utils/colorEnum.h"
#include <random>

GameManager::GameManager(int line, int column, int numPlyrs, bool randomPos) noexcept
	: mapManager(new MapManager(line, column)), running(false), autoMoveSmart(new AutoMoveSmart(mapManager)) 
{
	//Used for non deterministic random placement generation
	std::random_device rd;
	std::mt19937 gen(rd()); //Merseene Twister based
	std::uniform_int_distribution<> disLine(0, line - 1); // Uniformise in the given range
	std::uniform_int_distribution<> disColumn(0, column - 1); // Same as above for cols


    // Create players and store them in a vector
    for (int i = 1; i <= numPlyrs; i++) {
		std::shared_ptr<Player> p;
		bool positionSet = false;
		while (!positionSet) {
			if (randomPos) {
				int x = disLine(gen);
				int y = disColumn(gen);
				if (!*this->getMapManager()->getGrid()->getCell(x, y).getEntity()) {
					p = this->createPlayer("Player " + std::to_string(i), x, y, i);
					positionSet = true;
				}
			} else {
				if (!*this->getMapManager()->getGrid()->getCell(i, 0).getEntity()) {
					p = this->createPlayer("Player " + std::to_string(i), i, 0, i);
					positionSet = true;
				}
			}
		}
		pVector.emplace_back(p);
    };

	//Init maxn and paranoid algorithms
	maxn = new MaxnAlgorithm(mapManager);
	paranoid = new ParanoidAlgorithm(mapManager);
}

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

void GameManager::pauseGame() {
	this->pause = !this->pause;
}

bool GameManager::isRunning() const noexcept {
	return this->running;
}

void GameManager::threadLoop() {
	running = true;
	while (running) {
		if (this->pause) {continue;}

		// Auto move the players
		for (auto& player : pVector) {
			if (player->isPlayerDead()) {continue;}

			// Decide the best next move
			std::pair<std::pair<int, int>, int> res = autoMoveSmart->decideMove(player, 1);

			// Coords saving before any move
			auto [newX, newY] = res.first;
			int oldX = player->getCoords().x;
			int oldY = player->getCoords().y;

			if (newX == oldX && newY == oldY) { 
				std::cout << player->getName() << " tragically died at coords " << oldX << " " << oldY << std::endl;
				player->killPlayer();
				continue;
			}

			//Move the player and set a wall at the old position
			this->mapManager->setEntityAtCoords(player, newX, newY);
			this->mapManager->placeWallAtCoords(player.get(), oldX, oldY);

			//Draw the map
			std::cout << "\033[2J\033[H";
			this->draw();
			std::cout << "Press 'P' to pause the game. Press 'S' to stop the game" << std::endl;
			SLEEP_MS(500);
		} 
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

std::shared_ptr<Player> GameManager::createPlayer(std::string name, int i, int y, int uniqueInt) const {
	std::shared_ptr<Player> entity = std::make_shared<Player>(name, TCoords{ i, y }, Color::intToColor(uniqueInt), uniqueInt);
	this->getMapManager()->setEntityAtCoords(entity, i, y);
	return entity;
}

std::vector<int> GameManager::callMaxn(int depth) const {
	return this->maxn->maxn(pVector, depth, 0);
}

std::vector<int> GameManager::callParanoid(int depth) const {
	return this->paranoid->paranoid(pVector, depth, 0);
}

const std::vector<std::shared_ptr<Player>>& GameManager::getPlayers() const noexcept {
	return pVector;
}

int GameManager::getNumPlayers() const noexcept {
	return pVector.size();
}

const std::shared_ptr<Player>& GameManager::getPlayer(int i) const noexcept {
	return pVector[i];
}