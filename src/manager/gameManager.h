#pragma once

#include "entityManager.h"
#include "mapManager.h"
#include "../utils/utils.h"

#include <thread>
#include <iostream>

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

private:	
	std::thread gameThread;
	bool running;
	MapManager* mapManager;
	void threadLoop();
};