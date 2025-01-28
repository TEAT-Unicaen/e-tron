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

	bool setEntityAtCoords(GameEntity ent, int x, int y);
	bool setEntityAtCoords(GameEntity ent, TCoords coords);

	bool swapCell(TCoords coords1, TCoords coords2);

private:

	Grid* grid;
};