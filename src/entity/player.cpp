#include "player.h"

Player::Player(std::string name, TCoords coords, int color, int id) 
    : GameEntity(name, coords, color), id(id) {
}

Player::~Player() {
}

int Player::getId() {
	return id;
}