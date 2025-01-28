#include "./manager/gameManager.h"
#include <iostream>

int main() {

	std::cout << "Welcome to the game !\n" << std::endl;

	GameManager gameManager(3, 3);
	gameManager.debugEntity();
	std::cout << "DEFAULT GRID :" << std::endl;
	gameManager.draw();
	SLEEP(1);
	gameManager.getMapManager()->swapCell({ 0,0 }, { 1,1 });
	gameManager.draw();
	SLEEP(5);
	std::cout << "Starting the game !" << std::endl;
	gameManager.loop();
	SLEEP(5);

	gameManager.stop();
	std::cout << std::endl << "End of the game !" << std::endl;

    return 0;
}