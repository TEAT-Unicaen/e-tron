#pragma once

#include "../drawable.h"
#include "../../meshes/mesh.h"
#include "../../bindable/bindableBase.h"

class InstancedMeshDrawable : public Drawable {
public:
	InstancedMeshDrawable(
		Renderer& renderer,
		dx::XMFLOAT3 startPosition,
		dx::XMFLOAT3 startRotation,
		Mesh& mesh,
		std::wstring vertexShaderName,
		std::wstring pixelShaderName,
		std::vector<Color> colors,
		std::vector<dx::XMMATRIX> instances
	);

	InstancedMeshDrawable(
		Renderer& renderer,
		dx::XMFLOAT3 startPosition,
		dx::XMFLOAT3 startRotation,
		Mesh& mesh,
		std::wstring vertexShaderName,
		std::wstring pixelShaderName,
		Color color,
		std::vector<dx::XMMATRIX> instances
	);

	void draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE) override;

	void init(
		Renderer& renderer,
		dx::XMFLOAT3 startPosition,
		dx::XMFLOAT3 startRotation,
		Mesh& mesh,
		std::wstring vertexShaderName,
		std::wstring pixelShaderName,
		std::vector<dx::XMMATRIX> instances
	);
protected:
	UINT instanceCount;
};

#define MAX_COLORS 10