#include "gameManager.h"
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
    for (int i = 0; i <= numPlyrs; i++) {
		Player p;
		bool positionSet = false;
		while (!positionSet) {
			if (randomPos) {
				int x = disLine(gen);
				int y = disColumn(gen);
				if (!this->getMapManager()->getGrid()->getCell(x, y).getEntity()) {
					p = this->createPlayer("Player " + std::to_string(i), x, y, i);
					positionSet = true;
				}
			} else {
				if (!this->getMapManager()->getGrid()->getCell(i, 0).getEntity()) {
					p = this->createPlayer("Player " + std::to_string(i), i, 0, i);
					positionSet = true;
				}
			}
		}
		pVector.emplace_back(p);
    }
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

		// Auto move the players
		for (auto& player : pVector) {
			// Decide the best next move
			std::pair<std::pair<int, int>, int> res = autoMoveSmart->decideMove(player, 2);

			// Coords saving before any move
			auto [newX, newY] = res.first;
			int oldX = player.getCoords().x;
			int oldY = player.getCoords().y;

			//Move the player and set a wall at the old position
			this->mapManager->setEntityAtCoords(player, newX, newY);
			this->mapManager->placeWallAtCoords(&player, oldX, oldY);

			//Draw the map
			std::cout << "\033[2J\033[H";
			this->draw();
			SLEEP(1);
		}


		/*for (auto* updatable : this->updatables) {
			if (updatable) {
				updatable->update(); // je crois que AutoMoveSmart peut le faire solo voir pour le virer 
			} else {
				throw ETRON_EXCEPT("Invalid updatable, there is a null here wtf");
			}
		}*/
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

std::vector<Player> GameManager::getPlayers() const noexcept {
	return pVector;
}

int GameManager::getNumPlayers() const noexcept {
	return pVector.size();
}

Player GameManager::getPlayer(int i) const noexcept {
	return pVector[i];
}