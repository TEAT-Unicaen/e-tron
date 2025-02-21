#include "cube.h"

Cube::Cube(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity)
	: Drawable(renderer, startPosition, startRotation, velocity, angularVelocity) {
	this->addBindable(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	this->addBindable(std::make_unique<TransformConstantBuffer>(renderer, *this));
}

void Cube::update(float delta) noexcept {
	// Translation
	this->position.x += this->velocity.x * delta;
	this->position.y += this->velocity.y * delta;
	this->position.z += this->velocity.z * delta;

	// Rotation
	this->rotation.x += this->angularVelocity.x * delta;
	this->rotation.y += this->angularVelocity.y * delta;
	this->rotation.z += this->angularVelocity.z * delta;
}

// Returns the transformation matrix for the cube
dx::XMMATRIX Cube::getTransform() const {
	return dx::XMMatrixRotationRollPitchYaw(this->rotation.x, this->rotation.y, this->rotation.z) *
			dx::XMMatrixTranslation(this->position.x, this->position.y, this->position.z);
}
