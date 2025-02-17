#pragma once

#include <string>
#include <memory>
#include "../entity/gameEntity.h"


class Cell {
public:
    Cell() noexcept;
    Cell(const std::string& name) noexcept;
    ~Cell() = default;
    
    std::shared_ptr<GameEntity> getEntity() const noexcept;
	void setEntity(std::shared_ptr<GameEntity> ent) noexcept;
    std::string getName() const noexcept;

private:
    std::shared_ptr<GameEntity> entity;
    std::string name; 
};
