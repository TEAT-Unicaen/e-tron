#pragma once

#include "mapManager.h"
#include "../utils/utils.h"
#include "../utils/updatable.h"
#include "../utils/eTronException.h"
#include "../algorithms/maxnAlgorithm.h"
#include "../algorithms/paranoidAlgorithm.h"
#include "../algorithms/autoMoveSmart.h"

#include <thread>
#include <iostream>
#include <vector>

class GameManager {
public:
	// Constructor
	GameManager(int line, int column) noexcept;
	~GameManager();

	// Methods
	void draw() const noexcept;

	// Setters
	void setMapManager(MapManager* mapManager) noexcept;

	// Getters
	MapManager* getMapManager() const noexcept;

	void loop();
	void stop();

	void addUpdatable(IUpdatable* updatable) noexcept;
	std::vector<IUpdatable*> getUpdatables() const noexcept;

	Player createPlayer(std::string name, int i, int y, int color);
    MaxnAlgorithm callMaxn();
	ParanoidAlgorithm callParanoid();

private:

	std::thread gameThread;
	bool running;
	MapManager* mapManager;
	std::vector<IUpdatable*> updatables;
	AutoMoveSmart* autoMoveSmart;


	void threadLoop();
};