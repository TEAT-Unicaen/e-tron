#include "./manager/gameManager.h"
#include "./manager/inputManager.h"
#include "./mainFunctions.h"

#include <iostream>
#include <vector>
#include <windows.h>

#include "utils/eTronException.h"

int main() {
    try {
		MainFunctions mainFunctions;
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
        mainFunctions.setWritePipe(hWritePipe);
        mainFunctions.writeToPipe("Pipe connected\n");

        // Init managers
        GameManager gameManager(9, 9, 4, true);
        InputManager inputManager(gameManager, mainFunctions);

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
        mainFunctions.writeToPipe("Game is starting...\n");
        mainFunctions.writeToPipe("THIS IS A PLACEHOLDER FOR ADDITIONAL LOGGING AND ALGORITHM OUTPUT\n");

        SLEEP(10);
        gameManager.pauseGame();
        //Retrieve players scores in order
        std::vector<int> res = gameManager.callParanoid(2);
        std::string str = "Paranoid result at depth = 2 : ";
        for (int i = 0; i < res.size(); i++) {
            mainFunctions.writeToPipe("Player " + std::to_string(i+1) + " score for depth 2 is : " + std::to_string(res[i]) + "\n");
        }
        gameManager.pauseGame();

        // Handle inputs and game termination | Used as a wait for the moment
        while (gameManager.isRunning()) {
            inputManager.processInput();
        }

        gameManager.stop();
        Sleep(1000);

        // Send a message to the second terminal when the game stops
        mainFunctions.writeToPipe("Game has stopped.\n");

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
