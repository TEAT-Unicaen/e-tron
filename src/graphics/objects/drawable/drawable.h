#pragma once

#include <array>

#include "../../core/render/renderer.h"
#include "../bindable/bindable.h"
#include "../bindable/buffers/indexBuffer.h"
#include "../bindable/shaders/shaderManager.h"

namespace dx = DirectX;

class Drawable {
public:
	Drawable() = default;
	Drawable(Renderer& renderer, const dx::XMFLOAT3 startPosition, const dx::XMFLOAT3 startRotation, const dx::XMFLOAT3 velocity, const dx::XMFLOAT3 angularVelocity);
	Drawable(const Drawable&) = delete;
	virtual ~Drawable() = default;
	
	dx::XMMATRIX getTransform() const;
	virtual void draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE);
	virtual void update(float delta) noexcept;
	void addBindable(std::shared_ptr<Bindable> pBindables) noexcept;
	void addBindable(std::shared_ptr<IndexBuffer> pIndexBuffer) noexcept(!IS_DEBUG_MODE);

	static ShaderManager shaderManager;
protected:
	dx::XMFLOAT3 position = dx::XMFLOAT3(0.0f, 0.0f, 0.0f);
	dx::XMFLOAT3 rotation = dx::XMFLOAT3(0.0f, 0.0f, 0.0f);

	dx::XMFLOAT3 velocity = dx::XMFLOAT3(0.0f, 0.0f, 0.0f);
	dx::XMFLOAT3 angularVelocity = dx::XMFLOAT3(0.0f, 0.0f, 0.0f);
private:
	void bindAll(Renderer& renderer) const noexcept(!IS_DEBUG_MODE);
	UINT indexCount = 0u;
	std::vector<std::shared_ptr<Bindable>> pBindables;
};