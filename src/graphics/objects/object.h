#pragma once

#include "basicObjects/drawable.h"

class Object {
public:
	Object() = default;
	Object(const Object&) = delete;
	virtual ~Object() = default;
	
	void add(std::unique_ptr<Drawable> pDrawable) noexcept;
	void draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE);
	void update(float delta) noexcept;
private:
	std::vector<std::unique_ptr<Drawable>> pDrawables;
};