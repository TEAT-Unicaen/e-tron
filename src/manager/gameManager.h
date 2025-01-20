#pragma once

#include "entityManager.h"
#include "mapManager.h"

class GameManager {

public:

	// Constructor
	GameManager(int line, int column);
	~GameManager();

	// Methods
	void Start();

	// Setters
	void setMapManager(MapManager* mapManager);

	// Getters
	MapManager* getMapManager();

private:

	MapManager* mapManager;

};