#include "mainFunctions.h"
#include <windows.h>
#include <iostream>

bool MainFunctions::writeToPipe(const std::string& message) {
    DWORD written;
    return WriteFile(this->getWritePipe(), message.c_str(), message.size(), &written, NULL);
}

void MainFunctions::setWritePipe(HANDLE wp) {
    this->hWritePipe = wp;
}

HANDLE MainFunctions::getWritePipe() {
    return this->hWritePipe;
}
