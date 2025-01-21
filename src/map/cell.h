#pragma once

#include <string>
#include "../entity/gameEntity.h"


class Cell {

public:
    Cell();
    Cell(const std::string& name);
    ~Cell();
    
	GameEntity getEntity() const;
	void setEntity(GameEntity ent);
    std::string getName() const;

private:

	GameEntity entity;
    std::string name; 
};
