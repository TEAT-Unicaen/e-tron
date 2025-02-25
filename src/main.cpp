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

        // Waiting for the reader.exe pipe to be created safely with retries
        HANDLE hWritePipe;
        const int maxRetries = 10;
        const int delayMs = 100;
        for (int i = 0; i < maxRetries; ++i) {
            hWritePipe = CreateFile("\\\\.\\pipe\\GamePipe", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
            if (hWritePipe != INVALID_HANDLE_VALUE) {
                break;
            }

            if (i == maxRetries - 1) { 
                throw ETRON_EXCEPT("Main Failed to get reader handle"); 
            }
            Sleep(delayMs);
        }
        mainFunctions.setWritePipe(hWritePipe);
        mainFunctions.writeToPipe("Pipe connected\n");

        // Init managers
        GameManager gameManager(8, 8, 4, true);
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

        Sleep(10000);
		//FOR GUI TESTING
		//mainFunctions.LaunchGUIWithContext(&gameManager);

        //////// TEST ////////
        gameManager.pauseGame();
        //
        // 
        ////PARANOID : Retrieve players scores in order
        //std::vector<int> res = gameManager.callParanoid(10);
        //std::string str = "Paranoid result at depth = 10 : ";
        //for (int i = 0; i < res.size(); i++) {
        //    mainFunctions.writeToPipe("Player " + std::to_string(i+1) + " score for depth 2 is : " + std::to_string(res[i]) + "\n");
        //}

        //MAXN : Retrieve players scores in order
        std::vector<int> res = gameManager.callMaxn(10);
        std::string str = "Maxn result at depth = 10 : ";
        for (int i = 1; i < res.size(); i++) {
            mainFunctions.writeToPipe("Player " + std::to_string(i) + " score for depth 10 is : " + std::to_string(res[i]) + "\n");
        }

        //
        gameManager.pauseGame();
        //////////////////////

        // Handle inputs and game termination | Used as a wait for the moment
        while (gameManager.isRunning() && !gameManager.shouldStopCmd()) {
            inputManager.processInput();
        }

		// Stop the game
		if (gameManager.shouldStopCmd()) {
			std::cout << "Game has switched to GUI.\n";
            Sleep(300);
        } else {
            gameManager.stop();
            Sleep(1000);
        }

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
