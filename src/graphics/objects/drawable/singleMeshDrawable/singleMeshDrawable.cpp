#include "singleMeshDrawable.h"

SingleMeshDrawable::SingleMeshDrawable(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, Mesh& mesh, std::wstring vertexShaderName, std::wstring pixelShaderName, std::vector<Color> colors)
	: Drawable(renderer, startPosition, startRotation) {

	this->addBindable(mesh.vertexBuffer);
	this->addBindable(mesh.indexBuffer);

	auto pvs = shaderManager.getVertexShader(vertexShaderName);
	auto pvsbc = pvs->getBytecode();
	this->addBindable(std::move(pvs));
	this->addBindable(shaderManager.getPixelShader(pixelShaderName));

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

	//the layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	this->addBindable(std::make_shared<InputLayout>(renderer, inputElementDesc, pvsbc));

	this->addBindable(std::make_shared<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	this->addBindable(std::make_shared<TransformConstantBuffer>(renderer, *this));
	
}