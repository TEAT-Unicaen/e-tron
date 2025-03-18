#pragma once

#include "mapManager.h"
#include "../utils/utils.h"
#include "../utils/dataLinker.h"
#include "../utils/eTronException.h"
#include "../algorithms/analysis/maxnAlgorithm.h"
#include "../algorithms/analysis/paranoidAlgorithm.h"
#include "../algorithms/moving/movingAlgorithmsManager.h"
#include "../utils/colorEnum.h"
#include "../utils/jsonWriter.h"
#include "dataLogManager.h"

#include <thread>
#include <iostream>
#include <vector>
#include <memory>

class GameManager {
public:
	// Constructor
	GameManager(int line, int column, int numPlyrs, bool randomPos, bool useSos, bool drawEachStep, int waitAmountInMS, bool isAutomatedCall, DataLinker* dlHandler) noexcept;
	~GameManager();

	// Methods
	void draw() const noexcept;
	void loop();
	void stop();
	void pauseGame();
	bool areAllPlayerDead() const noexcept;

	// Setters
	void setMapManager(MapManager* mapManager) noexcept;

	// Getters and setters 
	MapManager* getMapManager() const noexcept;
	const std::vector<std::shared_ptr<Player>>& getPlayers() const noexcept;
	int getNumPlayers() const noexcept;
	const std::shared_ptr<Player>& getPlayer(int i) const noexcept;
	bool GameManager::isRunning() const noexcept;
	bool GameManager::shouldStopCmd() const noexcept;
	void GameManager::setStopCmd(bool stopCmd) noexcept;
	bool isPaused() const noexcept;

	std::shared_ptr<Player> createPlayer(std::string name, int i, int y, int uniqueInt) const;
	std::vector<int> callMaxn(int depth) const;
	std::vector<int> callParanoid(int depth) const;

private:

	std::thread gameThread;
	bool running;
	bool pause = false;
	bool stopCmd = false;
	bool effectivelyPaused = false;
	bool shouldUseSos;
	bool shouldDraw;
	bool isAutomated;
	int waitAmount;
	DataLinker* dataLinkerHandle;
	MovingAlgorithmsManager* movingAlgorithmsManager;
	MapManager* mapManager;
	AutoMoveSmart* autoMoveSmart;
	MaxnAlgorithm* maxn;
	ParanoidAlgorithm* paranoid;
	JsonWriter* jsonWriter;
	DataLogManager* dataLogManager;
	std::vector<std::shared_ptr<Player>> pVector;

	void threadLoop();
};