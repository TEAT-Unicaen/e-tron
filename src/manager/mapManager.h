#pragma once
#include "../map/grid.h"
#include "../entity/gameEntity.h"
#include "../entity/player.h"

class MapManager {
public:
	MapManager(int line, int column) noexcept;
	~MapManager() = default;

	// Methods
	void renderMap() const noexcept;
	void restoreCell(int x, int y) noexcept;
	void placeWallAtCoords(Player* owner, int x, int y);

	bool setEntityAtCoords(std::shared_ptr<GameEntity> ent, int x, int y);
	bool setEntityAtCoords(std::shared_ptr<GameEntity> ent, TCoords coords);

	// Setters
	void setGrid(Grid* grid) noexcept;

	// Getters
	Grid* getGrid() const noexcept;


private:
	Grid* grid;
};
