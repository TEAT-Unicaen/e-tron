#pragma once

#include "cell.h"
#include "../entity/gameEntity.h"
#include "../utils/eTronException.h"

class Grid {
public:
	Grid(int line, int column);
	~Grid() noexcept;

	int getLine() const noexcept;
	int getColumn() const noexcept;
	void renderGrid() const noexcept;
	void setCell(Cell& targetCell, GameEntity ent) noexcept;
	void initCell(int i, int j) noexcept;

	Cell& getCell(int i, int j) const;

private:	
	int line;
	int column;
	Cell** grid;
};