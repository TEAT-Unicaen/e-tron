#include "cell.h"

Cell::Cell() noexcept
	: name("Unnamed"), entity(new GameEntity()) {}


Cell::Cell(const std::string& name) noexcept
	: name(name), entity(new GameEntity()) {}

std::shared_ptr<GameEntity> Cell::getEntity() const noexcept {
	return this->entity;
}

void Cell::setEntity(std::shared_ptr<GameEntity> ent) noexcept {
	this->entity = ent;
}

std::string Cell::getName() const noexcept {
    return name;
}
