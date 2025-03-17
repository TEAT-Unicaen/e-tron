#include "skyBox.h"

SkyBox::SkyBox(Renderer& renderer, std::shared_ptr<Image> pImage, float size)
	: Drawable(
		renderer,
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f)
	) {
		
	// Vertex buffer
	Mesh mesh = Sphere(renderer, -size);

	this->addBindable(mesh.vertexBuffer);
	this->addBindable(mesh.indexBuffer);

	// Texture
	std::shared_ptr<Texture> pTexture = std::make_shared<Texture>(renderer, *pImage);
	this->addBindable(pTexture);
	this->addBindable(std::make_shared<SamplerState>(renderer));

	// Shader
	auto pvs = shaderManager.getVertexShader(L"texturedVS");
	auto pvsbc = pvs->getBytecode();
	this->addBindable(std::move(pvs));
	this->addBindable(shaderManager.getPixelShader(L"texturedPS"));

	// Topology
	this->addBindable(std::make_shared<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	
	const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	this->addBindable(std::make_shared<InputLayout>(renderer, inputElementDesc, pvsbc));
	this->addBindable(std::make_shared<TransformConstantBuffer>(renderer, *this));
}