#include "gameEntity.h"
#include <iostream>

GameEntity::GameEntity() noexcept
	: name(""), coords({ -1,-1 }), color(-1) {
}

GameEntity::GameEntity(std::string name, TCoords coords, int color) noexcept
	: name(name), coords(coords), color(color) {}

std::string GameEntity::getName() const noexcept {
	return this->name;
}

TCoords GameEntity::getCoords() const noexcept {
	return this->coords;
}

int GameEntity::getColor() const noexcept {
	return this->color;
}

void GameEntity::setCoords(TCoords coords) noexcept {
	this->coords = coords;
}