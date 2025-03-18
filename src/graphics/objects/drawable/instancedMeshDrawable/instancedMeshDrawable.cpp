#include "instancedMeshDrawable.h"

InstancedMeshDrawable::InstancedMeshDrawable(
		Renderer& renderer,
		dx::XMFLOAT3 startPosition,
		dx::XMFLOAT3 startRotation,
		Mesh& mesh,
		std::wstring vertexShaderName,
		std::wstring pixelShaderName
	)
	: Drawable(renderer, startPosition, startRotation) {
	this->addBindable(mesh.vertexBuffer);
	this->addBindable(mesh.indexBuffer);
	auto pvs = shaderManager.getVertexShader(vertexShaderName);
	auto pvsbc = pvs->getBytecode();
	this->addBindable(std::move(pvs));
	this->addBindable(shaderManager.getPixelShader(pixelShaderName));

	//the instance buffer
	auto pib = std::make_shared<InstanceBuffer>(renderer, 1u, 1);
	this->pInstanceBuffer = pib.get();
	this->addBindable(std::move(pib));

	//the layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc = {
		// Per-vertex data
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Normal",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},

		// Per-instance
		{"InstanceTransform", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0,  D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"InstanceTransform", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"InstanceTransform", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"InstanceTransform", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"Color",			  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64, D3D11_INPUT_PER_INSTANCE_DATA, 1}
	};
	this->addBindable(std::make_shared<InputLayout>(renderer, inputElementDesc, pvsbc));
	this->addBindable(std::make_shared<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	this->addBindable(std::make_shared<TransformConstantBuffer>(renderer, *this));
}

InstanceBuffer& InstancedMeshDrawable::getInstanceBuffer() noexcept {
	return *this->pInstanceBuffer;
}

void InstancedMeshDrawable::draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE) {
	this->bindAll(renderer);
	renderer.drawIndexedInstanced(this->indexCount, this->pInstanceBuffer->getCount());
}
