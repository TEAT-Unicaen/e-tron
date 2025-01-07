#pragma once

#include "cell.h"

class Grid {

public:
	Grid(int line, int column);
	~Grid();

	int getLine() const;
	int getColumn() const;

	Cell& getCell(int line, int column);

private:	

	int line;
	int column;
	Cell** grid;
};