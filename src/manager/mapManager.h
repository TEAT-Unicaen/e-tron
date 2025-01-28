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

protected:
	bool applyMove(GameEntity ent, int x, int y);
	bool applyMove(GameEntity ent, TCoords coords);

private:

	Grid* grid;
};