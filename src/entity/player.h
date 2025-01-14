#pragma once

#include "gameEntity.h"

class Player : public GameEntity {

public:

	Player(std::string name, TCoords coords, int color, int id);
	~Player();

	int getId();

private:

	int id;

};