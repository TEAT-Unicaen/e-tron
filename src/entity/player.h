#pragma once

#include "gameEntity.h"

class Player : public GameEntity {
public:
	Player(std::string name, TCoords coords, int color, int id) noexcept;
	~Player() = default;

	int getId() const noexcept;
private:
	int id;
};