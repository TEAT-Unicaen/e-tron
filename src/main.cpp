#include "./manager/gameManager.h"
#include <iostream>
#include <vector>

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

		GameManager gameManager(9, 9); 
		std::cout << "DEFAULT GRID :" << std::endl;
		gameManager.draw();

		//Alghorithms
		std::vector<Player> pVector;
		for (int i = 0; i <= 4; i++) {
			Player p = gameManager.createPlayer("Player "+std::to_string(i), i, 0, i);
			pVector.emplace_back(p);
		}
		gameManager.draw();
		ParanoidAlgorithm maxnAlg = gameManager.callParanoid();


		std::cout << "Starting the game !" << std::endl;

		
		std::vector<int> pResult = maxnAlg.paranoid(pVector, 5, 0);
		printVec(pResult);

		std::cout << "LOOP : " << std::endl;
		SLEEP(1);
		gameManager.loop();
		SLEEP(5);
		gameManager.stop();

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