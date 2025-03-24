#include "player.h"

Player::Player() noexcept
	: GameEntity(), id(-1), isDead(false) {
}

Player::Player(std::string name, TCoords coords, ColorE::ColorEnum color, int id) noexcept
    : GameEntity(name, coords, color), id(id), isDead(false), baseColor(color) {
}

int Player::getId() const noexcept {
	return id;
}

bool Player::isPlayerDead() {
	return this->isDead;
}

void Player::killPlayer() {
	this->isDead = true;
	this->name = "Dead P" + std::to_string(this->id);
	this->color = ColorE::ColorEnum::Red;
}

void Player::revive() {
	this->isDead = false;
	this->name = "Player " + std::to_string(this->id);
	this->color = this->baseColor;
}