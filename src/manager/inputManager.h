#pragma once
#include <iostream>
#include "gameManager.h"
#include "../utils/mainFunctions.h"

class InputManager {
public:
    InputManager(GameManager* gameManager, MainFunctions& mainFunctions);
    void processInput();

private: 
    GameManager* gameManager;
	MainFunctions& mainFunctions;
};
