#pragma once
#include <iostream>
#include "gameManager.h"

class InputManager {
public:
    InputManager(GameManager& gameManager);
    void processInput();

private: 
    GameManager& gameManager;
};
