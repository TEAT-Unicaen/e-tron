#pragma once

#include <string>
#include "../entity/gameEntity.h"


class Cell {
public:
    Cell() noexcept;
    Cell(const std::string& name) noexcept;
    ~Cell() = default;
    
	GameEntity getEntity() const noexcept;
	void setEntity(GameEntity ent) noexcept;
    std::string getName() const noexcept;

private:
	GameEntity entity;
    std::string name; 
};
