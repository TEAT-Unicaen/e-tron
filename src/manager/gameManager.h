#pragma once

#include "entityManager.h"
#include "mapManager.h"
#include "../utils/utils.h"
#include "../utils/updatable.h"
#include "../algorithms/maxnAlgorithm.h"

#include <thread>
#include <iostream>
#include <vector>

class GameManager {

public:

	// Constructor
	GameManager(int line, int column);
	~GameManager();

	// Methods
	void draw();

	// Setters
	void setMapManager(MapManager* mapManager);

	// Getters
	MapManager* getMapManager();

	void loop();
	void stop();

	void addUpdatable(IUpdatable* updatable);
	std::vector<IUpdatable*> getUpdatables();

	Player createPlayer(std::string name, int i, int y, int color);
    MaxnAlgorithm callMaxn();

private:

	std::thread gameThread;
	bool running;
	MapManager* mapManager;
	std::vector<IUpdatable*> updatables;

	void threadLoop();
};