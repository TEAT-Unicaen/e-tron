#include "maxnAlgorithm.h"
#include <iostream>
#include <vector>
#include <limits>
#include <cassert>

// Maxn maximise its score, considering it is alone.
// Basically function as a Minimax but with multiple players.

MaxnAlgorithm::MaxnAlgorithm(MapManager* mapMan) : AlgorithmUtils(mapMan) {
}

// TODO : IMPLEMENT TERRITORY AWARENESS

// Core Algorithme Maxn
std::vector<int> MaxnAlgorithm::maxn(std::vector<std::shared_ptr<Player>> players, int depth, int currentPlayer) {
    int numPlayers = players.size();

    // Recur : end case -> return all scores for the current state
    if (depth == 0) {
        std::vector<int> scores(numPlayers + 1, 0);
        for (int i = 0; i < numPlayers; i++) {
            if (!players[i]->isPlayerDead()) {
                scores[players[i]->getId()] = this->evaluate(players[i]);
            }
        }
        return scores;
    }

    // Check if all players are dead
    bool allPlayersDead = true;
    for (const auto& player : players) {
        if (!player->isPlayerDead()) {
            allPlayersDead = false;
            break;
        }
    }
    if (allPlayersDead) {
        return std::vector<int>(numPlayers + 1, 0); // Return zero scores if all players are dead
    }

    std::shared_ptr<Player> player = players[currentPlayer];
    assert(player != nullptr); // Ensure player is not null
    int playerId = player->getId();

    // Skip dead players
    if (player->isPlayerDead()) {
        return this->maxn(players, depth, (currentPlayer + 1) % numPlayers);
    }

    std::vector<int> bestScores(numPlayers + 1, INIT_VALUE);

    bool hasValidMove = false;
    for (auto& [newX, newY] : this->getAvailableMoves(player)) {
        hasValidMove = true;

        // Save state and move
        int oldX = player->getCoords().x;
        int oldY = player->getCoords().y;
        assert(this->getStoredMapMan() != nullptr); // Ensure map manager is not null
        this->getStoredMapMan()->setEntityAtCoords(player, newX, newY);

        // Recur on next player
        std::vector<int> scores = this->maxn(players, depth - 1, (currentPlayer + 1) % numPlayers);

        // Restore
        this->getStoredMapMan()->setEntityAtCoords(player, oldX, oldY);
        this->getStoredMapMan()->restoreCell(newX, newY);

        // Update score if needed
        if (scores[playerId] > bestScores[playerId]) {
            if (bestScores[playerId] == INIT_VALUE) {
                bestScores = scores;
            }
            else {
                for (int i = 0; i < numPlayers; i++) {
                    bestScores[i] += scores[i];
                }
            }
        }
    }

    // If no valid move, consider the player as dead for this branch
    if (!hasValidMove) {
        player->killPlayer();
        bestScores = this->maxn(players, depth - 1, (currentPlayer + 1) % numPlayers);
        player->revive(); // Restore the player's state
    }

    return bestScores;
}

