#pragma once

#include "player.h"
#include "gameEntity.h"
#include <string>

class Wall : public GameEntity {

public:

	Wall(std::string name, TCoords coords, int color, Player* owner);
	~Wall();

	Player* getOwner();

private:

	Player* owner;

};