#include "./manager/gameManager.h"
#include <iostream>
#include <vector>

#include "utils/tronException.h"

int main() {
	try {
		std::cout << "Welcome to the game !\n" << std::endl;

		GameManager gameManager(9, 9); 
		std::cout << "DEFAULT GRID :" << std::endl;
		gameManager.draw();
		SLEEP(5);

		//Alghorithms
		std::vector<Player> pVector;
		for (int i = 0; i <= 4; i++) {
			Player p = gameManager.createPlayer("Player " + i, i, i + 1, i);
			pVector.emplace_back(p);
		}
		gameManager.draw();
		MaxnAlgorithm maxnAlg = gameManager.callMaxn();


		std::cout << "Starting the game !" << std::endl;
		gameManager.loop();
		SLEEP(500);
		gameManager.stop();

	} catch (const TronException& e) {
		std::cerr << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Unknown exception" << std::endl;
	}


	std::cout << std::endl << "End of the game !" << std::endl;

    return 0;
}