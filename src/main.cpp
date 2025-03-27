#include "./manager/gameManager.h"
#include "./manager/inputManager.h"
#include "./utils/mainFunctions.h"
#include "./utils/configLoader.h"
#include "./algorithms/moving/movingAlgorithmsManager.h"

#include <iostream>
#include <vector>
#include <windows.h>

#include "utils/eTronException.h"

int main() {
    try {
		// Assert the file exists
        std::string configFilePath = "config.ini";
        if (!std::filesystem::exists(configFilePath)) {
            std::cerr << "Config file not found: " << configFilePath << std::endl;
            return 1;
        }

        ConfigLoader config(configFilePath);
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
        const int delayMs = 200;
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
		int numPlayers = config.getInt("num_players");
        int size = config.getInt("grid_size", numPlayers); 
		bool rdPos = config.getBool("use_random_pos", true);
        bool fixedDepth = config.getBool("fixed_depth", false);
        int fixed_depth_range = config.getInt("fixed_depth_range", 3);
		int depthsMin = config.getInt("depths_min", 3);
        int depthsInterval = config.getInt("depths_interval", 3);
		bool showEachStep = config.getBool("show_each_step", true);
		int waitAmount = config.getInt("wait_amount", 100);
        std::string algo = config.getString("algo", "BFS");

		std::cout << "Grid size : " << size << std::endl;
		std::cout << "Number of players : " << numPlayers << std::endl;
		std::cout << "Random position : " << rdPos << std::endl;
		std::cout << "Show each step : " << showEachStep << std::endl;
        std::cout << "Wait between each step (MS) : " << waitAmount << std::endl;

        std::vector<int> depths(numPlayers);

        std::cout << "Depth min : " << depthsMin << std::endl;
        std::cout << "Fixed depth : " << fixedDepth << std::endl;
        for (int i = 0; i < numPlayers; i++) {
            if (!fixedDepth) {
                depths[i] = (((i / depthsInterval) + 1) * depthsInterval) + depthsMin;
            }
            else {
                depths[i] = fixed_depth_range;
            }
        }

        MovingAlgorithmsManager::AlgoEnum algoEnum;

        if (algo == "BFS") {
            algoEnum = MovingAlgorithmsManager::AlgoEnum::BFS;
        }
        else if (algo == "SOS") {
            algoEnum = MovingAlgorithmsManager::AlgoEnum::SOS;
        }
        else {
            algoEnum = MovingAlgorithmsManager::AlgoEnum::SMART;
        }
        
        std::cout << "Algorithm : " << algo << std::endl;

        GameManager gameManager(size, size, numPlayers, rdPos, algoEnum, depths, showEachStep, waitAmount, false, NULL);
        InputManager inputManager(&gameManager, mainFunctions);

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
        mainFunctions.writeToPipe("Game commands :\n- 'P' pauses the game\n- 'S' Stops the game\n- 'M' Launches a MAXN report\n- 'N' Launches a Paranoid report");


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