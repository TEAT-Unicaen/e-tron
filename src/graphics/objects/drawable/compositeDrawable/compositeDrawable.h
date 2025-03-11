#pragma once

#include "../drawable.h"

class CompositeDrawable : public Drawable {
public:
	CompositeDrawable(Renderer& renderer, const dx::XMFLOAT3 startPosition, const dx::XMFLOAT3 startRotation, const dx::XMFLOAT3 scale = dx::XMFLOAT3(1.0f, 1.0f, 1.0f));
	virtual ~CompositeDrawable() = default;
	void addDrawable(std::unique_ptr<Drawable> pDrawable);

	void removeDrawable(UINT i);

	void draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE) override;
	void update(float delta) noexcept override;
private:
	std::vector<std::unique_ptr<Drawable>> pDrawables;
	
};