#include "inputManager.h"

InputManager::InputManager(GameManager* gameManager, MainFunctions& mainFunctions) : gameManager(gameManager), mainFunctions(mainFunctions) {}

void InputManager::processInput() {
    std::string input;
    std::cout << "Waiting for input: ";
    std::getline(std::cin, input);
    std::cout << "Input received: " << input << std::endl;

    if (input.empty()) {
        std::cout << "No input provided" << std::endl;
        return;
    }

    std::vector<int> res;

    switch (input[0]) {
        case 'p':
            gameManager->pauseGame();
            break;
        case 's':
            gameManager->stop();
            break;
        case 'm': 
			gameManager->pauseGame();
			//Retrieve players scores in order
            res = gameManager->callMaxn(10);
            mainFunctions.writeToPipe("Maxn result at depth = 10 : ");
			for (int i = 0; i < res.size(); i++) {
                mainFunctions.writeToPipe("Player " + std::to_string(i+1) +  " score for depth 10 is : " + std::to_string(res[i]) + "\n");
			}
            gameManager->pauseGame();
            break;
		case 'n':
			gameManager->pauseGame();
            //Retrieve players scores in order
            res = gameManager->callParanoid(10);
            mainFunctions.writeToPipe("Paranoid result at depth = 10 and tracked player = 1: ");
            for (int i = 0; i < res.size(); i++) {
                mainFunctions.writeToPipe("Player " + std::to_string(i+1) + " score for depth 10 is : " + std::to_string(res[i]) + "\n");
            }
			gameManager->pauseGame();
			break;
        default:
            std::cout << "Invalid key : " << input << std::endl;
            break;
    }
}
