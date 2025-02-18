#include "inputManager.h"

InputManager::InputManager(GameManager& gameManager) : gameManager(gameManager) {}

void InputManager::processInput() {
    std::string input;
    std::cout << "Waiting for input: ";
    std::getline(std::cin, input);
    std::cout << "Input received: " << input << std::endl;

    if (input.empty()) {
        std::cout << "No input provided" << std::endl;
        return;
    }

    switch (input[0]) {
        case 'p':
            gameManager.pauseGame();
            break;
        case 's':
            gameManager.stop();
            break;
        default:
            std::cout << "Invalid wtf " << input << std::endl;
            break;
    }
}
