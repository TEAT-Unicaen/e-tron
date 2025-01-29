#include "cell.h"

Cell::Cell() noexcept
	: name("Unnamed"), entity(entity) {}


Cell::Cell(const std::string& name) noexcept
	: name(name), entity(entity) {}

GameEntity Cell::getEntity() const noexcept {
	return this->entity;
}

void Cell::setEntity(GameEntity ent) noexcept {
	this->entity = ent;
}

std::string Cell::getName() const noexcept {
    return name;
}
