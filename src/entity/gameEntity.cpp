#include "gameEntity.h"

GameEntity::GameEntity() : name(NULL), coords({ -1,-1 }), color(-1) {}

GameEntity::GameEntity(std::string name, TCoords coords, int color)
	: name(name), coords(coords), color(color) {}

GameEntity::~GameEntity() {}


std::string GameEntity::getName() {
	return name;
}

TCoords GameEntity::getCoords() {
	return coords;
}

int GameEntity::getColor() {
	return color;
}

void GameEntity::setCoords(TCoords coords) {
	this->coords = coords;
}