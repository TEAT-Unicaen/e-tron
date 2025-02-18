#include "./manager/gameManager.h"
#include "./manager/inputManager.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "utils/eTronException.h"

void printVec(const std::vector<int>& vec) {
	for (int i : vec) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

int main() {
	try {
		std::cout << "Welcome to the game !\n" << std::endl;

		//Init managers
		GameManager gameManager(9, 9, 4, true);
		InputManager inputManager(gameManager);

		//Displaying start grid
		std::cout << "DEFAULT GRID :" << std::endl;
		gameManager.draw();

		//Main execution
		std::cout << "Starting the game !" << std::endl;
		SLEEP(1);
		std::cout << "Game Loop : " << std::endl;
		gameManager.loop();
		while (!gameManager.isRunning()) {SLEEP_MS(50);}

		//Handle inputs and game termination
		while (gameManager.isRunning()) {
			inputManager.processInput();
		}

		gameManager.stop();
		SLEEP(1);

	} catch (const ETronException& e) {
		std::cerr << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Unknown exception" << std::endl;
	}

	std::cout << std::endl << "End of the game !" << std::endl;

    return 0;
}