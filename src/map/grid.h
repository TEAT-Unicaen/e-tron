#pragma once

#include "cell.h"
#include "../entity/gameEntity.h"

class Grid {

public:
	Grid(int line, int column);
	~Grid();

	int getLine() const;
	int getColumn() const;
	void renderGrid() const;
	void setCell(Cell& targetCell, GameEntity ent);

	Cell& getCell(int i, int j);

private:	

	int line;
	int column;
	Cell** grid;
};