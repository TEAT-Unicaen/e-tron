#include "graphicsGameEntity.h"

GraphicsGameEntity::GraphicsGameEntity(float x, float y, float z, Color color) noexcept
	: x(x), y(y), z(z), color(color) {
}

dx::XMFLOAT3 GraphicsGameEntity::getCoords() const noexcept {
	return dx::XMFLOAT3(x, y, z);
}

Color GraphicsGameEntity::getColor() const noexcept {
	return color;
}

void GraphicsGameEntity::setCoords(float x, float y, float z) noexcept {
	this->x = x;
	this->y = y;
	this->z = z;
}

void GraphicsGameEntity::removeVisual() {
	// TODO
}
