#include "cell.h"

Cell::Cell() : name("Unnamed"), entity(entity) {}


Cell::Cell(const std::string& name) : name(name), entity(entity) {}

Cell::~Cell() {}

GameEntity Cell::getEntity() const {
	return this->entity;
}

void Cell::setEntity(GameEntity ent) {
	this->entity = ent;
}

std::string Cell::getName() const {
    return name;
}
