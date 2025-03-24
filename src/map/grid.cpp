#include "grid.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Grid::Grid(int line, int column) 
	: line(line), column(column) {
	if (line <= 0 || column <= 0) {
		throw ETRON_EXCEPT("Invalid grid size");
	}

	grid = new Cell * [line];
	for (int i = 0; i < line; i++) {
		grid[i] = new Cell[column];
		for (int j = 0; j < column; j++) {
			this->initCell(i, j);
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

	int maxSizeName = 0;

	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			int nameSize = grid[i][j].getName().size();
			if (nameSize > maxSizeName) {
				maxSizeName = nameSize;
			}
		}
	}

	int cellWidth = maxSizeName + 2; 

	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			std::cout << "+" << std::string(cellWidth, '-');
		}
		std::cout << "+\n";

		for (int j = 0; j < column; j++) {
			GameEntity ent = *grid[i][j].getEntity();
			if (ent) {
                int padding = maxSizeName - ent.getName().size();
                std::cout << "| " << std::setw(maxSizeName) << std::left << ColorE::printColoredText(ent.getColor(), ent.getName()) << std::string(padding, ' ') << " ";
			} else {
				std::cout << "| " << std::setw(maxSizeName) << std::left << " " << " ";
			}
		}
		std::cout << "|\n";
	}

	for (int j = 0; j < column; j++) {
		std::cout << "+" << std::string(cellWidth, '-');
	}
	std::cout << "+\n";
}

Cell& Grid::getCell(int i, int j) const {
	if (i < 0 || i >= line || j < 0 || j >= column) {
		throw ETRON_EXCEPT("Invalid cell position");
	}
	return grid[i][j];
}

void Grid::setCell(Cell& targetCell, std::shared_ptr<GameEntity> ent) noexcept {
	targetCell.setEntity(ent);		
}

void Grid::initCell(int x, int y) noexcept {
	std::ostringstream cellName;
	cellName << "Cell(" << x << "," << y << ")";
	Cell cell(cellName.str());
	grid[x][y] = cell;
}