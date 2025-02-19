#include "material.h"

Material::Material(Material::Type type) 
	: type(type) {}

Material::Type Material::getType() const noexcept {
	return this->type;
}