#pragma once

#include <string>

typedef struct SCoords {
	int x;
	int y;
} TCoords;

class Wall {

public:

	GameEntity(std::string name, TCoords coords, int color);
	~GameEntity();

private:

	std::string name;
	TCoords coords;
	int color;
};