#include "./manager/gameManager.h"
#include "./manager/inputManager.h"
#include <iostream>
#include <vector>
#include <windows.h>

#include "utils/eTronException.h"

void printVec(const std::vector<int>& vec) {
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void writeToPipe(HANDLE hWritePipe, const std::string& message) {
    DWORD written;
    WriteFile(hWritePipe, message.c_str(), message.size(), &written, NULL);
}

int main() {
    try {
        std::cout << "Welcome to the game !\n" << std::endl;

        // Launching the second cmd with the reading program
        STARTUPINFO si = { sizeof(STARTUPINFO) };
        PROCESS_INFORMATION pi;
        if (CreateProcess(NULL, (LPSTR)"\"reader.exe\"", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
            std::cout << "Second terminal launched successfully.\n";
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        } else {
            std::cerr << "Failed to open second terminal.\n";
            return 1;
        }

        // Waiting for the reader.exe pipe to be created
        SLEEP(2);

        // Hood the named pipe for algorithms logging on a second terminal
        HANDLE hWritePipe;
		hWritePipe = CreateFile("\\\\.\\pipe\\GamePipe", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (hWritePipe == INVALID_HANDLE_VALUE) {
            std::cerr << "Failed to connect to pipe.\n";
            return 1;
        }
        writeToPipe(hWritePipe, "Pipe connected\n");


        // Init managers
        GameManager gameManager(9, 9, 4, true);
        InputManager inputManager(gameManager);

        // Displaying start grid
        Sleep(500);
        std::cout << "DEFAULT GRID :" << std::endl;
        gameManager.draw();

        // Main execution
        std::cout << "Starting the game !" << std::endl;
        Sleep(2000);
        std::cout << "Game Loop : " << std::endl;
        gameManager.loop();
        while (!gameManager.isRunning()) { Sleep(50); }

        // Send a message to the second terminal
        writeToPipe(hWritePipe, "Game is starting...\n");
        writeToPipe(hWritePipe, "THIS IS A PLACEHOLDER FOR ADDITIONAL LOGGING AND ALGORITHM OUTPUT\n");

        // Handle inputs and game termination
        while (gameManager.isRunning()) {
            inputManager.processInput();
        }

        gameManager.stop();
        Sleep(1000);

        // Send a message to the second terminal when the game stops
        writeToPipe(hWritePipe, "Game has stopped.\n");

    }
    catch (const ETronException& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception" << std::endl;
    }

    std::cout << std::endl << "End of the game !" << std::endl;

    return 0;
}
