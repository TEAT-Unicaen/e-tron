#include "squarePyramid.h"

SquarePyramid::SquarePyramid(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity)
	: Drawable(renderer, startPosition, startRotation, velocity, angularVelocity) {}

void SquarePyramid::update(float delta) noexcept {
	// Translation
	this->position.x += this->velocity.x * delta;
	this->position.y += this->velocity.y * delta;
	this->position.z += this->velocity.z * delta;

	// Rotation
	this->rotation.x += this->angularVelocity.x * delta;
	this->rotation.y += this->angularVelocity.y * delta;
	this->rotation.z += this->angularVelocity.z * delta;
}

dx::XMMATRIX SquarePyramid::getTransform() const {
	return dx::XMMatrixRotationRollPitchYaw(this->rotation.x, this->rotation.y, this->rotation.z) *
		dx::XMMatrixTranslation(this->position.x, this->position.y, this->position.z);
}