#include map/grid.h

Grid::Grid(int line, int column) : line(line), column(column) {

	this.grid = new Cell[line][column];

}