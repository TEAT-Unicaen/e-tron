#pragma once

#include <DirectXMath.h>
#include <array>

#include "../renderer.h"
#include "bindable/bindable.h"
#include "bindable/buffers/indexBuffer.h"

namespace dx = DirectX;

class Drawable {
public:
	Drawable() = default;
	Drawable(Renderer& renderer, const dx::XMFLOAT3 startPosition, const dx::XMFLOAT3 startRotation, const dx::XMFLOAT3 velocity, const dx::XMFLOAT3 angularVelocity);
	Drawable(const Drawable&) = delete;
	virtual ~Drawable() = default;
	
	dx::XMMATRIX getTransform() const;
	void draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE);
	void update(float delta) noexcept;
	void addBindable(std::unique_ptr<Bindable> pBindables) noexcept;
	void addIndexBuffer(std::unique_ptr<IndexBuffer> pIndexBuffer) noexcept(!IS_DEBUG_MODE);
protected:
	dx::XMFLOAT3 position;
	dx::XMFLOAT3 rotation;

	dx::XMFLOAT3 velocity;
	dx::XMFLOAT3 angularVelocity;
private:
	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> pBindables;

};