#include "gameEntity.h"

GameEntity::GameEntity() noexcept
	: name(NULL), coords({ -1,-1 }), color(-1) {}

GameEntity::GameEntity(std::string name, TCoords coords, int color) noexcept
	: name(name), coords(coords), color(color) {}

std::string GameEntity::getName() const noexcept {
	return name;
}

TCoords GameEntity::getCoords() const noexcept {
	return coords;
}

int GameEntity::getColor() const noexcept {
	return color;
}

void GameEntity::setCoords(TCoords coords) noexcept {
	this->coords = coords;
}