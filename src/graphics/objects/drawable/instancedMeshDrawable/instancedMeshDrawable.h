#pragma once

#include "../drawable.h"
#include "../../meshes/mesh.h"
#include "../../bindable/bindableBase.h"
#include "../../bindable/buffers/instanceBuffer.h"

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

	InstancedMeshDrawable(
		Renderer& renderer,
		dx::XMFLOAT3 startPosition,
		dx::XMFLOAT3 startRotation,
		Mesh& mesh,
		std::wstring vertexShaderName,
		std::wstring pixelShaderName,
		Color color
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

	void updateInstance(
		Renderer& renderer,
		UINT i,
		const dx::XMFLOAT3 position,
		const dx::XMFLOAT3 rotation,
		const dx::XMFLOAT3 scale = dx::XMFLOAT3(1.0f, 1.0f, 1.0f)
	);
	
	void addInstance(
		Renderer& renderer,
		dx::XMFLOAT3 Position,
		dx::XMFLOAT3 Rotation,
		Mesh& mesh,
		std::wstring vertexShaderName,
		std::wstring pixelShaderName,
		Color color
	);


protected:
	InstanceBuffer *pInstanceBuffer;
};

#define MAX_COLORS 10