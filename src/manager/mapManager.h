#pragma once
#include "../map/grid.h"
#include "../entity/gameEntity.h"

class MapManager {
public:
	MapManager(int line, int column) noexcept;
	~MapManager() = default;

	// Methods
	void renderMap() const noexcept;

	// Setters
	void setGrid(Grid* grid) noexcept;

	// Getters
	Grid* getGrid() const noexcept;

	bool setEntityAtCoords(GameEntity ent, int x, int y) noexcept;
	bool setEntityAtCoords(GameEntity ent, TCoords coords) noexcept;

	bool swapCell(TCoords coords1, TCoords coords2) noexcept;

private:
	Grid* grid;
};