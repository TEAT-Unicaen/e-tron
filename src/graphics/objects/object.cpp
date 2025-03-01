#include "object.h"

void Object::add(std::unique_ptr<Drawable> pDrawable) noexcept {
	this->pDrawables.push_back(std::move(pDrawable));
}

void Object::draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE) {
	for (const auto& d : this->pDrawables) {
		d->draw(renderer);
	}
}

void Object::update(float delta) noexcept {
	for (const auto& d : this->pDrawables) {
		d->update(delta);
	}
}