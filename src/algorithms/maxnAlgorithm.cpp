#include "maxnAlgorithm.h"
#include <iostream>
#include <vector>
#include <limits>

//Grid dimesions
int static gridLines;
int static gridCols;
Grid* storedGrid;

// Possible directions (up, down, left, right)
const std::vector<std::pair<int, int>> DIRECTIONS = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

MaxnAlgorithm::MaxnAlgorithm(Grid* grid) {
    gridLines = grid->getLine(); 
    gridCols = grid->getColumn();
    storedGrid = grid;
}

MaxnAlgorithm::~MaxnAlgorithm(){}

bool isValidMove(int x, int y) {
    return x >= 0 && x < gridCols && y >= 0 && y < gridLines && storedGrid->getCell(x,y).getEntity() == false; //Test if the check if working ?
}

std::vector<std::pair<int, int>> getAvailableMoves(Player player) {
    std::vector<std::pair<int, int>> moves;
    for (auto [dx, dy] : DIRECTIONS) { //Compiler auto detect type based on "DIRECTIONS" type.
        int newX = player.getCoords().x + dx;
        int newY = player.getCoords().y + dy;
        if (isValidMove(newX, newY)) {
            moves.emplace_back(newX, newY); //Equivalent to append or add in other languages.
        }
    }
    return moves;
}

// Return the score, alias "position quality" of a player, based on the move possibilities around him
int evaluate(Player player) {
	return getAvailableMoves(player).size();
}

// Core Algorithme Maxn
std::vector<int> maxn(std::vector<Player> players, int depth, int currentPlayer) {
	int numPlayers = players.size();

    //Recur : end case -> return all scores for the current state
    if (depth == 0) {
		std::vector<int> scores(numPlayers, 0);
		for (int i = 0; i < numPlayers; i++) {
			scores[i] = evaluate(players[i]);
		}
		return scores;
    }


	Player& player = players[currentPlayer];
	std::vector<int> bestScores(numPlayers, std::numeric_limits<int>::min()); //Workaround to init numPlayer elems at minimum int value (-2^63)

    for (auto [newX, newY] : getAvailableMoves(player)) {
		//TODO : implement algorithm
        //Save state
        //Recur on next plyr
        //Restore
        //Update score if needed
    }

    return bestScores;
}


/*Optis à mettre en place : 
- Elagage alpha-bêta pour eviter branches inutiles -> vectors de bornes pour chaque joueur ? (Minimax impossible car 2plyr et +)
- Heuristiques : 
    - Prendre en compte joueurs autour
    - ?
*/





