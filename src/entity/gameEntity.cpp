#include "gameEntity.h"

GameEntity::GameEntity(std::string name, TCoords coords, int color)
	: name(name), coords(coords), color(color) {
}

GameEntity::~GameEntity() {
}


std::string GameEntity::getName() {
	return name;
}

TCoords GameEntity::getCoords() {
	return coords;
}

int GameEntity::getColor() {
	return color;
}

