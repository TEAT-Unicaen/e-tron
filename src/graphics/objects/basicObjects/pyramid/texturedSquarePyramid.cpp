#include "texturedSquarePyramid.h"

TexturedSquarePyramid::TexturedSquarePyramid(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::shared_ptr<Image> pImage)
	: SquarePyramid(renderer, startPosition, startRotation, velocity, angularVelocity), pImage(pImage) {
	struct Vertex {
		dx::XMFLOAT3 pos;
		dx::XMFLOAT2 tex;
	};

	std::vector<Vertex> vertices = {
		// Base
		{dx::XMFLOAT3(-0.5f, -0.5f, -0.5f), dx::XMFLOAT2(2.0f / 3.0f, 1.0f / 3.0f)}, //0
		{dx::XMFLOAT3(0.5f, -0.5f, -0.5f), dx::XMFLOAT2(2.0f / 3.0f, 2.0f / 3.0f)}, //1
		{dx::XMFLOAT3(0.5f, -0.5f, 0.5f), dx::XMFLOAT2(1.0f / 3.0f, 2.0f / 3.0f)}, //2
		{dx::XMFLOAT3(-0.5f, -0.5f, 0.5f), dx::XMFLOAT2(1.0f / 3.0f, 1.0f / 3.0)}, //3

		// Sommet Front
		{dx::XMFLOAT3(0.0f, 0.5f, 0.0f), dx::XMFLOAT2(1.0f, 0.5f)}, //4
		// Sommet Right
		{dx::XMFLOAT3(0.0f, 0.5f, 0.0f), dx::XMFLOAT2(0.5f, 1.0f)}, //5
		// Sommet Back
		{dx::XMFLOAT3(0.0f, 0.5f, 0.0f), dx::XMFLOAT2(0.0f, 0.5f)}, //6
		// Sommet Left
		{dx::XMFLOAT3(0.0f, 0.5f, 0.0f), dx::XMFLOAT2(0.5f, 0.0f)}, //7
	};
	std::vector<unsigned short> indices = {
		// Base
		0, 1, 2,   0, 2, 3,
		// Faces
		0, 4, 1, // Front face
		1, 5, 2, // Right face
		2, 6, 3, // Back face
		3, 7, 0, // Left face
	};
	this->addBindable(std::make_shared<VertexBuffer>(renderer, vertices));
	this->addBindable(std::make_shared<IndexBuffer>(renderer, indices));

	auto pvs = shaderManager.getVertexShader(L"textureVS");
	auto pvsbc = pvs->getBytecode();
	this->addBindable(std::move(pvs));
	this->addBindable(shaderManager.getPixelShader(L"texturePS"));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	this->addBindable(std::make_shared<InputLayout>(renderer, inputElementDesc, pvsbc));

	// Bind the texture
	this->addBindable(std::make_shared<Texture>(renderer, *pImage));
	this->addBindable(std::make_shared<SamplerState>(renderer));
}