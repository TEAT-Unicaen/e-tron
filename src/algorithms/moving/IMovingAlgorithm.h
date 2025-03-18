#pragma once

class IMovingAlgorithm {
public:
    virtual ~IMovingAlgorithm() = default;
    virtual std::pair<std::pair<int, int>, int> decideMove(std::shared_ptr<Player> player, int depth, const std::vector<std::vector<double>>& W) = 0;
};
