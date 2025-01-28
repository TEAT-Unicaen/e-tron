#pragma once
#include "../map/grid.h"
#include "../entity/gameEntity.h"

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

	bool applyMove(GameEntity ent, int x, int y);
	bool applyMove(GameEntity ent, TCoords coords);

	bool swapCell(TCoords coords1, TCoords coords2);

private:

	Grid* grid;
};