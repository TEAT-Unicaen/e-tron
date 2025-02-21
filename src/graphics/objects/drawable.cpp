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