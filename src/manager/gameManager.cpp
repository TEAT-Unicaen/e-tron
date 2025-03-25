#include "gameManager.h"
#include "../entity/player.h"
#include "../utils/colorEnum.h"
#include "../utils/dataLinker.h"
#include "../algorithms/moving/movingAlgorithmsManager.h"
#include <random>

#include <Windows.h>

GameManager::GameManager(int line, int column, int numPlyrs, bool randomPos, bool useSos, bool drawEachStep, int waitAmountInMS, bool isAutomatedCall, DataLinker* dlHandler) noexcept
	: mapManager(new MapManager(line, column)), running(false), autoMoveSmart(new AutoMoveSmart(mapManager)) {

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

	//Init the algorithm manager
	movingAlgorithmsManager = new MovingAlgorithmsManager(mapManager);
	shouldUseSos = useSos;
	shouldDraw = drawEachStep;
	waitAmount = waitAmountInMS;
	isAutomated = isAutomatedCall;
	dataLinkerHandle = dlHandler;

	//Init json writer

	auto now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	std::ostringstream oss;
	oss << "result_" << millis << ".json";

	this->dataLogManager = new DataLogManager();
	this->jsonWriter = new JsonWriter(oss.str());
	std::cout << "Output file will be : " << oss.str() << std::endl;

	this->dataLogManager->addLog("numPlayers", numPlyrs);
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
	this->effectivelyPaused = false;
}

bool GameManager::isRunning() const noexcept {
	return this->running;
}

void GameManager::threadLoop() {
	running = true;
	int tick = 0;
	while (running) {
		if (this->pause) {
			this->effectivelyPaused = true;
			continue;
		}

		// Auto move the players
		for (auto& player : pVector) {
			if (player->isPlayerDead()) {continue;}

			// Matrix of affinities
			std::vector<std::vector<double>> W = {
				{0.5, 1.0, 1.0, 1.0, 1.0},
				{1.0, 0.5, 1.0, 1.0, 1.0},
				{1.0, 1.0, 0.5, 1.0, 1.0},
				{1.0, 1.0, 1.0, 0.5, 1.0},
				{1.0, 1.0, 1.0, 1.0, 0.5},
			};

			// Decide the best next move
			std::pair<std::pair<int, int>, int> res = movingAlgorithmsManager->useAlgorithm(this->shouldUseSos, player, 3, W);
			
			// Coords saving before any move
			auto [newX, newY] = res.first;
			int oldX = player->getCoords().x;
			int oldY = player->getCoords().y;

			if (newX == oldX && newY == oldY) { 
				std::cout << player->getName() << " tragically died at coords " << oldX << " " << oldY << std::endl;
				this->dataLogManager->addTick(tick, "dead " + player->getName());
				tick++;
				player->killPlayer();
				continue;
			}

			//Move the player and set a wall at the old position
			this->mapManager->setEntityAtCoords(player, newX, newY);
			this->mapManager->placeWallAtCoords(player.get(), oldX, oldY);

			int deltaX = newX - oldX;
			int deltaY = newY - oldY;

			std::string action;

			if (deltaY == 1) {
				action = "right";
			} else if (deltaY == -1) {
				action = "left";
			} else if (deltaX == 1) {
				action = "top";
			} else if (deltaX == -1) {
				action = "bottom";
			} 

			this->dataLogManager->addMovement(player->getName(), action, 1);

			this->dataLogManager->addTick(tick, action + " " + player->getName());

			//Draw the map
			if (this->isAutomated) {
				dataLinkerHandle->addData(player->getId(), oldX, oldY, newX, newY);
			} else if (this->shouldDraw) {
				std::cout << "\033[2J\033[H";
				this->draw();
				SLEEP_MS(this->waitAmount);
			}
			tick++;
		} 

		//Death handling and last redraw to keep updated
		if (this->areAllPlayerDead()) {
			if (!isAutomated) {this->draw();}
			std::cout << "All players are dead" << std::endl;
			//this->pause = true;
			this->running = false;
		}
	}
	//TODO include datas in json & build it 
	this->dataLogManager->fillJson(*this->jsonWriter);
	jsonWriter->writeJson(); //Write the json file
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

bool GameManager::areAllPlayerDead() const noexcept {
	for (auto& player : pVector) {
		if (!player->isPlayerDead()) {
			return false;
		}
	}
	return true;
}

std::shared_ptr<Player> GameManager::createPlayer(std::string name, int i, int y, int uniqueInt) const {
	std::shared_ptr<Player> entity = std::make_shared<Player>(name, TCoords{ i, y }, ColorE::intToColor(uniqueInt), uniqueInt);
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

bool GameManager::shouldStopCmd() const noexcept {
	return this->stopCmd;
}

void GameManager::setStopCmd(bool stopCmd) noexcept {
	this->stopCmd = stopCmd;
}

bool GameManager::isPaused() const noexcept {
	return this->effectivelyPaused;
}