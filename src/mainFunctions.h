#pragma once
#include <windows.h>
#include <string> 
#include "./manager/gameManager.h"

class MainFunctions {
public:
    bool writeToPipe(const std::string& message);
    void setWritePipe(HANDLE wp);
	void LaunchGUIWithContext(GameManager* context);

private:
    HANDLE hWritePipe;
    HANDLE getWritePipe();
};