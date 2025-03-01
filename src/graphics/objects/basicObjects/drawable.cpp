#include "drawable.h"

Drawable::Drawable(Renderer& renderer, const dx::XMFLOAT3 startPosition, const dx::XMFLOAT3 startRotation, const dx::XMFLOAT3 velocity, const dx::XMFLOAT3 angularVelocity)
	: position(startPosition), rotation(startRotation), velocity(velocity), angularVelocity(angularVelocity) {}

void Drawable::draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE) {
	for (const auto& b : this->pBindables) {
		b->bind(renderer);
	}
	renderer.drawIndexed(this->pIndexBuffer->getCount());
}

void Drawable::addBindable(std::unique_ptr<Bindable> pBindables) noexcept {
	assert("Use addIndexBuffer for index buffer" && typeid(*pBindables) != typeid(IndexBuffer));
	this->pBindables.push_back(std::move(pBindables));
}

void Drawable::addIndexBuffer(std::unique_ptr<IndexBuffer> pIndexBuffer) noexcept(!IS_DEBUG_MODE) {
	assert("Already set the index buffer!" && this->pIndexBuffer == nullptr);
	this->pIndexBuffer = pIndexBuffer.get();
	this->pBindables.push_back(std::move(pIndexBuffer));
}

void Drawable::update(float delta) noexcept {
	// Translation
	this->position.x += this->velocity.x * delta;
	this->position.y += this->velocity.y * delta;
	this->position.z += this->velocity.z * delta;

	// Rotation
	this->rotation.x += this->angularVelocity.x * delta;
	this->rotation.y += this->angularVelocity.y * delta;
	this->rotation.z += this->angularVelocity.z * delta;
}

dx::XMMATRIX Drawable::getTransform() const {
	return dx::XMMatrixRotationRollPitchYaw(this->rotation.x, this->rotation.y, this->rotation.z) *
		dx::XMMatrixTranslation(this->position.x, this->position.y, this->position.z);
}