#include "grid.h"
#include <iostream>
#include <sstream>

Grid::Grid(int line, int column) : line(line), column(column) {

	if (line <= 0 || column <= 0) {
		throw std::invalid_argument("Invalid grid size");
	}

	grid = new Cell * [line];
	for (int i = 0; i < line; i++) {
		grid[i] = new Cell[column];
		for (int j = 0; j < column; j++) {
			std::ostringstream cellName;
			cellName << "Cell(" << i << "," << j << ")";
			grid[i][j] = Cell(cellName.str()); 
		}
	}
}


Grid::~Grid() {
	for (int i = 0; i < line; i++) {
		delete[] grid[i];
	}
	delete[] grid;
}

int Grid::getLine() const {
	return line;
}

int Grid::getColumn() const {
	return column;
}

Cell& Grid::getCell(int i, int j) {
	if (i < 0 || i >= line || j < 0 || j >= column) {
		throw std::invalid_argument("Invalid cell position");
	}
	return grid[i][j];
}