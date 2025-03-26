#include "AutoMoveBFS.h"
#include <iostream>
#include <queue>
#include <unordered_set>

AutoMoveBFS::AutoMoveBFS(MapManager* mapMan) : AlgorithmUtils(mapMan) {}

int AutoMoveBFS::bfsArea(std::shared_ptr<Player> player) {
    std::queue<std::pair<int, int>> q;
    std::unordered_set<int> visited;

    auto startPos = player->getCoords();
    q.push({ startPos.x, startPos.y });
    visited.insert(startPos.x * 1000 + startPos.y);

    int areaSize = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        areaSize++;

        for (auto& [newX, newY] : this->getAvailableMoves(player)) {
            int hash = newX * 1000 + newY;
            if (visited.find(hash) == visited.end()) {
                visited.insert(hash);
                q.push({ newX, newY });
            }
        }
    }

    return areaSize;
}

std::pair<std::pair<int, int>, int> AutoMoveBFS::decideMoveBFS(std::shared_ptr<Player> player) {
    std::pair<int, int> bestMove = { player->getCoords().x, player->getCoords().y };
    int bestArea = -1;

    for (auto& [newX, newY] : this->getAvailableMoves(player)) {
        int oldX = player->getCoords().x;
        int oldY = player->getCoords().y;
        this->getStoredMapMan()->setEntityAtCoords(player, newX, newY);

        int areaSize = bfsArea(player);

        this->getStoredMapMan()->setEntityAtCoords(player, oldX, oldY);
        this->getStoredMapMan()->restoreCell(newX, newY);

        if (areaSize > bestArea) {
            bestArea = areaSize;
            bestMove = { newX, newY };
        }
    }

    return { bestMove, bestArea };
}