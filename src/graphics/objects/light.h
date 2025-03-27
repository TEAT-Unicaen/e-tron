#pragma once

#include "../core/render/renderer.h"
#include "meshes/meshes.h"
#include "drawable/singleMeshDrawable/singleMeshDrawable.h"
#include "bindable/buffers/constantBuffers/pixelConstantBuffer.h"

class Light {
public:
	struct LightBuffer {
		dx::XMFLOAT3 position;
		dx::XMFLOAT3 color;
		dx::XMFLOAT3 ambient;
		float diffuseIntensity;
		float attConst;
		float attLinear;
		float attQuad;
	};
	Light(Renderer& renderer, const dx::XMFLOAT3& pos, const Color color);
	Light(const Light&) = delete;
	~Light() = default;
	void draw(Renderer& renderer);
	LightBuffer getLightBufferData() const noexcept;
	void setPosition(const dx::XMFLOAT3& pos) noexcept;
	void setColor(Renderer& renderer, const Color color) noexcept;

	dx::XMFLOAT3 getPosition() const noexcept;
	Color getColor() const noexcept;
private:
	dx::XMFLOAT3 position;
	Color color;
	std::unique_ptr<Drawable> pObj;
	LightBuffer lightBufferData;
};