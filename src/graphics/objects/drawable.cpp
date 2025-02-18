#include "drawable.h"

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