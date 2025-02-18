#pragma once
#include <windows.h>
#include <string>

class MainFunctions {
public:
    bool writeToPipe(const std::string& message);
    void setWritePipe(HANDLE wp);

private:
    HANDLE hWritePipe;
    HANDLE getWritePipe();
};