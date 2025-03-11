#include  "compositeDrawable.h"

CompositeDrawable::CompositeDrawable(
	Renderer& renderer,
	const dx::XMFLOAT3 startPosition,
	const dx::XMFLOAT3 startRotation,
	const dx::XMFLOAT3 scale
)
	: Drawable(renderer, startPosition, startRotation, scale) {}

void CompositeDrawable::addDrawable(std::unique_ptr<Drawable> pDrawable) {
	pDrawables.push_back(std::move(pDrawable));
}

void CompositeDrawable::removeDrawable(UINT i) {
	pDrawables.erase(pDrawables.begin() + i);
}

void CompositeDrawable::draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE) {
	for (auto& pDrawable : pDrawables) {
		pDrawable->draw(renderer);
	}
}

void CompositeDrawable::update(float delta) noexcept {
	for (auto& pDrawable : pDrawables) {
		pDrawable->update(delta);
	}
}

