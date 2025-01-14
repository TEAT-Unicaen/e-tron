#include "wall.h"
#include "player.h"

Wall::Wall(std::string name, TCoords coords, int color, Player* owner)
    : GameEntity(name, coords, color), owner(owner) {
}

Wall::~Wall() {
}

Player* Wall::getOwner() {
	return owner;
}