#pragma once

#include "autoMoveSmart.h"
#include "autoMoveSos.h"
#include "autoMoveBFS.h"

class MovingAlgorithmsManager  {
public:

    enum class AlgoEnum {
        SMART,
		SOS,
		BFS
    };

    std::string algoEnumToString(AlgoEnum algo) {
        switch (algo) {
        case AlgoEnum::SMART: return "SMART";
        case AlgoEnum::SOS: return "SOS";
        case AlgoEnum::BFS: return "BFS";
        default: return "Unknown";
        }
    }


    MovingAlgorithmsManager(MapManager* mapMan);
    ~MovingAlgorithmsManager() = default;

    std::pair<std::pair<int, int>, int> useAlgorithm(AlgoEnum algo, std::shared_ptr<Player> player, int depth, int numP);

private:

	AutoMoveSmart autoMoveSmart;
	AutoMoveSos autoMoveSos;
    AutoMoveBFS autoMoveBFS;
};
