#include "dataLinker.h"
#include "configLoader.h"
#include "../manager/gameManager.h"

#include <windows.h>

DataLinker::DataLinker() {}

std::vector<std::pair<int, std::vector<int>>> DataLinker::requestData() {
    // Assert the file exists
    ConfigLoader config("config.ini");
	// Init managers
	int numPlayers = config.getInt("num_players");
	int size = config.getInt("grid_size", numPlayers);
	GameManager gameManager(size, size, numPlayers, config.getBool("use_random_pos", true), config.getBool("movement_use_SOS", false), false, 0, true, this);
	std::cout << "Game created" << std::endl;
	gameManager.loop();
	std::cout << "Game started" << std::endl;
	// Wait data
	while (!gameManager.isRunning()) { Sleep(5); }
	std::cout << "started run" << std::endl;
	while (gameManager.isRunning()) { Sleep(5); }
	std::cout << "end" << std::endl;
	gameManager.stop();
	return this->data;
}

void DataLinker::addData(int id, int x, int y, int newX, int newY) {
	this->data.push_back({id, {x, y, newX, newY}});
}

