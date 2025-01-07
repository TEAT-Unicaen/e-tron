#pragma once

class Grid {

public:
	Grid(int line, int column);
	~Grid();

private:	

	int line;
	int column;
	Cell[][] grid;
};