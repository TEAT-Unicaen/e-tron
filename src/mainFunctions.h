#pragma once
#include <windows.h>
#include <string> 
#include "./manager/gameManager.h"

class MainFunctions {
public:
    bool writeToPipe(const std::string& message);
    void setWritePipe(HANDLE wp);

private:
    HANDLE hWritePipe;
    HANDLE getWritePipe();
};