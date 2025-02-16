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
	GameManager(int line, int column, int numPlyrs, bool randomPos) noexcept;
	~GameManager();

	// Methods
	void draw() const noexcept;
	void loop();
	void stop();

	// Setters
	void setMapManager(MapManager* mapManager) noexcept;

	// Getters and setters 
	MapManager* getMapManager() const noexcept;
	std::vector<Player> getPlayers() const noexcept;
	int getNumPlayers() const noexcept;
	Player getPlayer(int i) const noexcept;

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
	std::vector<Player> pVector;


	void threadLoop();
};