#include <random>
#include "./affinitiesMatrixGenerator.h"

std::vector<std::vector<double>> AffinitiesMatrixGenerator::generateRandomAffinities(int numPlayers)
{
    std::vector<std::vector<double>> matrix(numPlayers, std::vector<double>(numPlayers));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < numPlayers; ++i) {
        for (int j = 0; j < numPlayers; ++j) {
            matrix[i][j] = dis(gen);
        }
    }

    return matrix;
}
