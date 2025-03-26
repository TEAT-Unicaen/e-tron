#pragma once

#include "../core/render/renderer.h"
#include "meshes/meshes.h"
#include "drawable/singleMeshDrawable/singleMeshDrawable.h"
#include "bindable/buffers/constantBuffers/pixelConstantBuffer.h"

class Light {
public:
	Light(Renderer& renderer, const dx::XMFLOAT3& pos, const Color color);
	~Light() = default;
	void draw(Renderer& renderer);
	void bind(Renderer& renderer);
	void setPosition(const dx::XMFLOAT3& pos) noexcept;
	void setColor(Renderer& renderer, const Color color) noexcept;

	dx::XMFLOAT3 getPosition() const noexcept;
	Color getColor() const noexcept;
private:
	struct LightBuffer {
		alignas(16) dx::XMFLOAT3 position;
		alignas(16) dx::XMFLOAT3 color;
		alignas(16) dx::XMFLOAT3 ambient;
		float diffuseIntensity;
		float attConst;
		float attLinear;
		float attQuad;
	};
	dx::XMFLOAT3 position;
	Color color;
	std::unique_ptr<Drawable> pObj;
	LightBuffer lightBufferData;
	PixelConstantBuffer<LightBuffer> lightBuffer;
};