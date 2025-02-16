#include "player.h"

Player::Player() noexcept
	: GameEntity() {
}

Player::Player(std::string name, TCoords coords, int color, int id) noexcept
    : GameEntity(name, coords, color), id(id) {
}

int Player::getId() const noexcept {
	return id;
}