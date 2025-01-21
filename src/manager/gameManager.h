#pragma once

#include "entityManager.h"
#include "mapManager.h"
#include "../entity/gameEntity.h"

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
	
	bool applyMove(GameEntity ent, TCoords coords);

	MapManager* mapManager;

};