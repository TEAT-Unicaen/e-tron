#include "instancedMeshDrawable.h"

InstancedMeshDrawable::InstancedMeshDrawable(
	Renderer& renderer,
	dx::XMFLOAT3 startPosition,
	dx::XMFLOAT3 startRotation,
	Mesh& mesh,
	std::wstring vertexShaderName,
	std::wstring pixelShaderName,
	std::vector<Color> colors,
	std::vector<dx::XMMATRIX> instances
	) 
	: Drawable(renderer, startPosition, startRotation) {

	this->init(renderer, startPosition, startRotation, mesh, vertexShaderName, pixelShaderName, instances);

	//the colors
	struct ColorBuffer {
		dx::XMFLOAT4 colors[MAX_COLORS];
		UINT colorsSize;
		float padding[3];
	};

	UINT colorsSize = colors.size();

	ColorBuffer cb = {};
	cb.colorsSize = colorsSize;
	for (UINT i = 0; i < colorsSize; i++) {
		cb.colors[i] = colors[i].toFloat4();
	}

	this->addBindable(std::make_shared<PixelConstantBuffer<ColorBuffer>>(renderer, cb, 0u));
}

InstancedMeshDrawable::InstancedMeshDrawable(
	Renderer& renderer,
	dx::XMFLOAT3 startPosition,
	dx::XMFLOAT3 startRotation,
	Mesh& mesh,
	std::wstring vertexShaderName,
	std::wstring pixelShaderName,
	Color color,
	std::vector<dx::XMMATRIX> instances
)
	: Drawable(renderer, startPosition, startRotation) {

	this->init(renderer, startPosition, startRotation, mesh, vertexShaderName, pixelShaderName, instances);

	//the colors
	struct ColorBuffer {
		dx::XMFLOAT4 colors[MAX_COLORS];
		UINT colorsSize;
		float padding[3];
	};

	ColorBuffer cb = {};
	cb.colors[0] = color.toFloat4();
	cb.colorsSize = 1;

	this->addBindable(std::make_shared<PixelConstantBuffer<ColorBuffer>>(renderer, cb, 0u));
}

InstancedMeshDrawable::InstancedMeshDrawable(
	Renderer& renderer,
	dx::XMFLOAT3 startPosition,
	dx::XMFLOAT3 startRotation,
	Mesh& mesh,
	std::wstring vertexShaderName,
	std::wstring pixelShaderName,
	Color color

) : Drawable(renderer, startPosition, startRotation) {

	std::vector<dx::XMMATRIX> instances = { dx::XMMatrixIdentity() };
	this->init(renderer, startPosition, startRotation, mesh, vertexShaderName, pixelShaderName, instances);

	//the colors
	struct ColorBuffer {
		dx::XMFLOAT4 colors[MAX_COLORS];
		UINT colorsSize;
		float padding[3];
	};

	ColorBuffer cb = {};
	cb.colors[0] = color.toFloat4();
	cb.colorsSize = 1;

	this->addBindable(std::make_shared<PixelConstantBuffer<ColorBuffer>>(renderer, cb, 0u));

}

void InstancedMeshDrawable::init(
	Renderer& renderer,
	dx::XMFLOAT3 startPosition,
	dx::XMFLOAT3 startRotation,
	Mesh& mesh,
	std::wstring vertexShaderName,
	std::wstring pixelShaderName,
	std::vector<dx::XMMATRIX> instances
	) {
	this->position = startPosition;
	this->rotation = startRotation;
	this->addBindable(mesh.vertexBuffer);
	this->addBindable(mesh.indexBuffer);
	auto pvs = shaderManager.getVertexShader(vertexShaderName);
	auto pvsbc = pvs->getBytecode();
	this->addBindable(std::move(pvs));
	this->addBindable(shaderManager.getPixelShader(pixelShaderName));

	//the instance buffer
	auto pib = std::make_shared<InstanceBuffer>(renderer, instances, 1u);
	this->pInstanceBuffer = pib.get();
	this->addBindable(std::move(pib));
	
	//the layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc = {
		// Per-vertex data
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},

		// Per-instance transformation matrix (4 x float4)
		{"InstanceTransform", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0,  D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"InstanceTransform", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"InstanceTransform", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"InstanceTransform", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1},
	};
	this->addBindable(std::make_shared<InputLayout>(renderer, inputElementDesc, pvsbc));
	this->addBindable(std::make_shared<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	this->addBindable(std::make_shared<TransformConstantBuffer>(renderer, *this));
}

void InstancedMeshDrawable::updateInstance(
	Renderer& renderer,
	UINT i,
	const dx::XMFLOAT3 position,
	const dx::XMFLOAT3 rotation,
	const dx::XMFLOAT3 scale
) {
	this->pInstanceBuffer->updateInstance(renderer, i, position, rotation, scale);
}

void InstancedMeshDrawable::addInstance(
	Renderer& renderer,
	dx::XMFLOAT3 Position,
	dx::XMFLOAT3 Rotation,
	Mesh& mesh,
	std::wstring vertexShaderName,
	std::wstring pixelShaderName,
	Color color
) {
	this->pInstanceBuffer->addInstance(renderer, Position, Rotation, dx::XMFLOAT3(1.0f, 1.0f, 1.0f));
}

void InstancedMeshDrawable::draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE) {
	this->bindAll(renderer);
	renderer.drawIndexedInstanced(this->indexCount, this->pInstanceBuffer->getCount());
}
