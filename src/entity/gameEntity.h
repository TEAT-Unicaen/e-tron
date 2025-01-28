#pragma once

#include <string>

typedef struct SCoords {
	int x;
	int y;
} TCoords;

class GameEntity {
	
public:
	GameEntity();
	GameEntity(std::string name, TCoords coords, int color);
	~GameEntity();

	std::string getName();
	TCoords getCoords();
	int getColor();
	void setCoords(TCoords coords);

	operator bool() const {
		return !name.empty() || color != -1 || (coords.x != -1 || coords.y != -1);
	}

protected:

	std::string name;
	TCoords coords;
	int color;

};