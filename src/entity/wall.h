#pragma once

#include "player.h"
#include "gameEntity.h"
#include <string>

class Wall : public GameEntity {
public:
	Wall(std::string name, TCoords coords, Color::ColorEnum color, Player* owner) noexcept;
	~Wall() = default;

	Player* getOwner() const noexcept;
private:
	Player* owner;
};