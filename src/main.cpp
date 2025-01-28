#include "./manager/gameManager.h"
#include <iostream>

int main() {

	std::cout << "Welcome to the game !\n" << std::endl;

	GameManager gameManager(3, 3);
	gameManager.loop();
	_sleep(5000);
	gameManager.stop();
	std::cout << std::endl << "End of the game !" << std::endl;

    return 0;
}