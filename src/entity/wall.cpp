#include "wall.h"


Wall::Wall(std::string name, TCoords coords, ColorE::ColorEnum color, Player* owner) noexcept
    : GameEntity(name, coords, color), owner(owner) {
}

Player* Wall::getOwner() const noexcept {
	return owner;
}