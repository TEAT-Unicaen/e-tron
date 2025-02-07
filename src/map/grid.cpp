#include "grid.h"
#include <iostream>
#include <sstream>

Grid::Grid(int line, int column) 
	: line(line), column(column) {
	if (line <= 0 || column <= 0) {
		throw ETRON_EXCEPT("Invalid grid size");
	}

	grid = new Cell * [line];
	for (int i = 0; i < line; i++) {
		grid[i] = new Cell[column];
		for (int j = 0; j < column; j++) {
			std::ostringstream cellName;
			cellName << "Cell(" << i << "," << j << ")";
			Cell cell(cellName.str());
			grid[i][j] = cell; 
		}
	}
}

Grid::~Grid() noexcept {
	for (int i = 0; i < line; i++) {
		delete[] grid[i];
	}
	delete[] grid;
}

int Grid::getLine() const noexcept {
	return line;
}

int Grid::getColumn() const noexcept {
	return column;
}

void Grid::renderGrid() const noexcept {
	// First line
	for (int k = 0; k < column-1; ++k) {
		Cell& cell = grid[0][k];
		std::cout << std::string(cell.getName().length(), '-');
	}
	std::cout << std::endl;

	// Main grid
	for (int i = 0; i < line; ++i) {
		for (int j = 0; j < column; ++j) {
			Cell& cell = grid[i][j];
		
			if (cell.getEntity().getName().length() > 0) {
				std::cout << "| " << cell.getEntity().getName() << "  ";
			}
			else {
				std::cout << "| " << "     " << " ";
			}
		}
		std::cout << "|" << std::endl;

		for (int k = 0; k < column-1; ++k) {
			Cell& cell = grid[i][k];
			std::cout << std::string(cell.getName().length(), '-');
		}
		std::cout << std::endl;
	}
}

Cell& Grid::getCell(int i, int j) const {
	if (i < 0 || i >= line || j < 0 || j >= column) {
		throw ETRON_EXCEPT("Invalid cell position");
	}
	return grid[i][j];
}

void Grid::setCell(Cell& targetCell, GameEntity ent) noexcept {
	targetCell.setEntity(ent);		
}