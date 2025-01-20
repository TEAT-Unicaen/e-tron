#pragma once
#include "../map/grid.h"

class MapManager {

public:

	MapManager(int line, int column);
	~MapManager();

	// Methods
	void renderMap();

	// Setters
	void setGrid(Grid* grid);

	// Getters
	Grid* getGrid();

private:

	Grid* grid;

};