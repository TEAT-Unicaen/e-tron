#include "AutoMoveSos.h"
#include <iostream>
#include <vector>
#include <limits>
#include <cassert>

// SOS is a MAXN with "affinities" between players.
// This version is used for moving players in the game, with strategical moves.

AutoMoveSos::AutoMoveSos(MapManager* mapMan) : AlgorithmUtils(mapMan) {}

// Core Algorithme SOS
std::pair<std::pair<int, int>, int> AutoMoveSos::decideMove(std::shared_ptr<Player> player, int depth, const std::vector<std::vector<double>>&W) {
    std::pair<int, int> nextPos = { player->getCoords().x, player->getCoords().y }; // Init next pos at actual pos in case of no move possible
    int bestScore = -1;
    // Recur : end case -> return the score for the current placement
    if (depth == 0) {
        int score = this->evaluate(player);
        return { nextPos, score };
    }

    for (auto& [newX, newY] : this->getAvailableMoves(player)) {
        // Save state and move
        int oldX = player->getCoords().x;
        int oldY = player->getCoords().y;
        this->getStoredMapMan()->setEntityAtCoords(player, newX, newY);

        // Recur on the next position
        std::pair<std::pair<int, int>, int> res = this->decideMove(player, depth - 1, W);
        int score = res.second;

        // Adjust score based on affinities
        for (int i = 0; i < W.size(); i++) {
            score = static_cast<int>(score * W[player->getId()][i]);
        }

        // Restore
        this->getStoredMapMan()->setEntityAtCoords(player, oldX, oldY);
        this->getStoredMapMan()->restoreCell(newX, newY);

        if (score >= bestScore) {
            bestScore = score;
            nextPos = { newX, newY };
        }
    }

    return {nextPos, bestScore};
}

