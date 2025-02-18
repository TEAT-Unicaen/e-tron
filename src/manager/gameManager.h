#pragma once

#include "mapManager.h"
#include "../utils/utils.h"
#include "../utils/eTronException.h"
#include "../algorithms/maxnAlgorithm.h"
#include "../algorithms/paranoidAlgorithm.h"
#include "../algorithms/autoMoveSmart.h"
#include "../utils/colorEnum.h"

#include <thread>
#include <iostream>
#include <vector>
#include <memory>

class GameManager {
public:
	// Constructor
	GameManager(int line, int column, int numPlyrs, bool randomPos) noexcept;
	~GameManager();

	// Methods
	void draw() const noexcept;
	void loop();
	void stop();
	void pauseGame();

	// Setters
	void setMapManager(MapManager* mapManager) noexcept;

	// Getters and setters 
	MapManager* getMapManager() const noexcept;
	const std::vector<std::shared_ptr<Player>>& getPlayers() const noexcept;
	int getNumPlayers() const noexcept;
	const std::shared_ptr<Player>& getPlayer(int i) const noexcept;
	bool GameManager::isRunning() const noexcept;

	std::shared_ptr<Player> createPlayer(std::string name, int i, int y, int uniqueInt) const;
	std::vector<int> callMaxn(int depth) const;
	std::vector<int> callParanoid(int depth) const;

private:

	std::thread gameThread;
	bool running;
	bool pause = false;
	MapManager* mapManager;
	AutoMoveSmart* autoMoveSmart;
	MaxnAlgorithm* maxn;
	ParanoidAlgorithm* paranoid;
	std::vector<std::shared_ptr<Player>> pVector;

	void threadLoop();
};