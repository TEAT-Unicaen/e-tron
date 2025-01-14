#pragma once

#include <string>

typedef struct SCoords {
	int x;
	int y;
} TCoords;

class GameEntity {
	
public:

	GameEntity(std::string name, TCoords coords, int color);
	~GameEntity();

	std::string getName();
	TCoords getCoords();
	int getColor();

protected:

	std::string name;
	TCoords coords;
	int color;

};