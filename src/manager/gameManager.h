#pragma once

#include "entityManager.h"
#include "mapManager.h"
#include "../utils/utils.h"
#include "../utils/updatable.h"

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

	void debugEntity();

private:

	std::thread gameThread;
	bool running;
	MapManager* mapManager;
	std::vector<IUpdatable*> updatables;

	void threadLoop();
};