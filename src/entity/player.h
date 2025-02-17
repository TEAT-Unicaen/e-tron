#pragma once

#include "gameEntity.h"

class Player : public GameEntity {
public:
	Player() noexcept;
	Player(std::string name, TCoords coords, Color::ColorEnum color, int id) noexcept;
	~Player() = default;

	int getId() const noexcept;
	bool isPlayerDead();
	void killPlayer();

private:
	int id;
	bool isDead;
};