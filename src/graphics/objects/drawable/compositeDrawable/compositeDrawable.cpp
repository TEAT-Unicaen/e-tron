#include  "compositeDrawable.h"

CompositeDrawable::CompositeDrawable(
	Renderer& renderer,
	const dx::XMFLOAT3 startPosition,
	const dx::XMFLOAT3 startRotation,
	const dx::XMFLOAT3 scale
)
	: Drawable(renderer, startPosition, startRotation, scale),
	pVcBuffer(std::make_shared<VertexConstantBuffer<dx::XMMATRIX>>(renderer, 1u)) {}

void CompositeDrawable::addDrawable(std::unique_ptr<Drawable> pDrawable) {
	pDrawable->addBindable(pVcBuffer);
	pDrawables.push_back(std::move(pDrawable));
}

void CompositeDrawable::removeDrawable(UINT i) {
	pDrawables.erase(pDrawables.begin() + i);
}

void CompositeDrawable::draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE) {
	this->pVcBuffer->update(renderer, dx::XMMatrixTranspose(this->getTransform()));
	for (auto& pDrawable : pDrawables) {
		pDrawable->draw(renderer);
	}
}

void CompositeDrawable::update(float delta) noexcept {
	Drawable::update(delta);
	for (auto& pDrawable : pDrawables) {
		pDrawable->update(delta);
	}
}

