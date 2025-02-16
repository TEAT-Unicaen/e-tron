#include "algorithmUtils.h"
#include <vector>
#include <utility>
#include <iostream>


//Grid dimesions
int static gridLines;
int static gridCols;
Grid* storedGrid;
MapManager* storedMapMan;

AlgorithmUtils::AlgorithmUtils(MapManager* mapMan) {
	storedGrid = mapMan->getGrid();
	storedMapMan = mapMan;
	gridLines = storedGrid->getLine();
	gridCols = storedGrid->getColumn();
}

// Possible directions (up, down, left, right)
const std::vector<std::pair<int, int>> DIRECTIONS = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

bool AlgorithmUtils::isAValidMove(int x, int y) {
    if (x < 0 || x >= gridCols || y < 0 || y >= gridLines) {
        return false;
    }
    return !storedGrid->getCell(x, y).getEntity();
}

std::vector<std::pair<int, int>> AlgorithmUtils::getAvailableMoves(Player player) {
    std::vector<std::pair<int, int>> moves;
    for (auto [dx, dy] : DIRECTIONS) { //Compiler auto detect type based on "DIRECTIONS" type.
        int newX = player.getCoords().x + dx;
        int newY = player.getCoords().y + dy;
        if (this->isAValidMove(newX, newY)) {
            moves.emplace_back(newX, newY); //Equivalent to append or add in other languages.
        }
    }
    return moves;
}

// Return the score, alias "position quality" of a player, based on the move possibilities around him
int AlgorithmUtils::evaluate(Player player) {
    return this->getAvailableMoves(player).size();
}

MapManager* AlgorithmUtils::getStoredMapMan() {
	return storedMapMan;
}