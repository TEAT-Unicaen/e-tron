#pragma once
#include "algorithmUtils.h"

class ParanoidAlgorithm : public AlgorithmUtils {
public:

	// Constructor
	ParanoidAlgorithm(MapManager* mapMan);
	~ParanoidAlgorithm() = default;

	//Methods
	std::vector<int> paranoid(std::vector<std::shared_ptr<Player>> players, int depth, int currentPlayer);
};

