#pragma once

#include <DirectXMath.h>

#include "../renderer.h"
#include "bindable/bindable.h"
#include "bindable/buffers/indexBuffer.h"

namespace dx = DirectX;

class Drawable {
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual ~Drawable() = default;
	
	virtual dx::XMMATRIX getTransform() const = 0;
	void draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE);
	virtual void update(float delta) noexcept = 0;
	void addBindable(std::unique_ptr<Bindable> pBindables) noexcept;
	void addIndexBuffer(std::unique_ptr<IndexBuffer> pIndexBuffer) noexcept(!IS_DEBUG_MODE);
private:
	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> pBindables;
};