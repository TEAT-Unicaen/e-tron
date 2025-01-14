#include "gameEntity.h"

GameEntity::GameEntity(std::string name, TCoords coords, int color) {
	this->name = name;
	this->coords = coords;
	this->color = color;
}