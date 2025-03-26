#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

class AffinitiesMatrixGenerator {
public:
	AffinitiesMatrixGenerator() = default;
    ~AffinitiesMatrixGenerator() = default;

    static std::vector<std::vector<double>> generateRandomAffinities(int numPlayers);
};
