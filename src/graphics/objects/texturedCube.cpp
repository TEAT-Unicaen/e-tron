#include "texturedCube.h"

TexturedCube::TexturedCube(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::shared_ptr<Image> pImage)
	: Cube(renderer, startPosition, startRotation, velocity, angularVelocity), pImage(pImage) {
	
	struct Vertex {
		dx::XMFLOAT3 pos;
		dx::XMFLOAT2 tex;
	};

	float cubeTextureSize = 1.0f / 3.0f;

	float haut = 2.0f / 3.0f;
	float bas = 1.0f / 3.0f;

	std::vector<Vertex> vertices = {
		// Face avant
		{dx::XMFLOAT3(-0.5f, 0.5f, -0.5f), dx::XMFLOAT2(haut, 1.0f / 4.0f)}, // Haut gauche
		{dx::XMFLOAT3(0.5f, 0.5f, -0.5f), dx::XMFLOAT2(haut, 2.0f / 4.0f)}, // Haut droite
		{dx::XMFLOAT3(0.5f, -0.5f, -0.5f), dx::XMFLOAT2(bas, 2.0f / 4.0f)}, // Bas droite
		{dx::XMFLOAT3(-0.5f, -0.5f, -0.5f), dx::XMFLOAT2(bas, 1.0f / 4.0f)}, // Bas gauche

		// Face arrière
		{dx::XMFLOAT3(-0.5f, 0.5f, 0.5f), dx::XMFLOAT2(haut, 1.0f)}, // Haut gauche
		{dx::XMFLOAT3(0.5f, 0.5f, 0.5f), dx::XMFLOAT2(haut, 3.0f / 4.0)}, // Haut droite
		{dx::XMFLOAT3(0.5f, -0.5f, 0.5f), dx::XMFLOAT2(bas, 3.0f / 4.0f)}, // Bas droite
		{dx::XMFLOAT3(-0.5f, -0.5f, 0.5f), dx::XMFLOAT2(bas, 1.0f)}, // Bas gauche

		// Face gauche
		{dx::XMFLOAT3(-0.5f, 0.5f, 0.5f), dx::XMFLOAT2(haut, 0.0f)}, // Haut gauche
		{dx::XMFLOAT3(-0.5f, 0.5f, -0.5f), dx::XMFLOAT2(haut, 1.0f / 4.0f)}, // Haut droite
		{dx::XMFLOAT3(-0.5f, -0.5f, -0.5f), dx::XMFLOAT2(bas, 1.0f / 4.0f)}, // Bas droite
		{dx::XMFLOAT3(-0.5f, -0.5f, 0.5f), dx::XMFLOAT2(bas, 0.0f)}, // Bas gauche

		// Face droite
		{dx::XMFLOAT3(0.5f, 0.5f, 0.5f), dx::XMFLOAT2(haut, 3.0f / 4.0f)}, // Haut gauche
		{dx::XMFLOAT3(0.5f, 0.5f, -0.5f), dx::XMFLOAT2(haut, 2.0f / 4.0f)}, // Haut droite
		{dx::XMFLOAT3(0.5f, -0.5f, -0.5f), dx::XMFLOAT2(bas, 2.0f / 4.0f)}, // Bas droite
		{dx::XMFLOAT3(0.5f, -0.5f, 0.5f), dx::XMFLOAT2(bas, 3.0f / 4.0f)}, // Bas gauche

		// Face haut
		{dx::XMFLOAT3(-0.5f, 0.5f, 0.5f), dx::XMFLOAT2(1.0f, 1.0f / 4.0)}, // Haut gauche
		{dx::XMFLOAT3(0.5f, 0.5f, 0.5f), dx::XMFLOAT2(1.0f, 2.0f / 4.0f)}, // Haut droite
		{dx::XMFLOAT3(0.5f, 0.5f, -0.5f), dx::XMFLOAT2(haut, 2.0f / 4.0f)}, // Bas droite
		{dx::XMFLOAT3(-0.5f, 0.5f, -0.5f), dx::XMFLOAT2(haut, 1.0f / 4.0)}, // Bas gauche

		// Face bas
		{dx::XMFLOAT3(-0.5f, -0.5f, 0.5f), dx::XMFLOAT2(0.0f, 1.0f / 4.0)}, // Haut gauche
		{dx::XMFLOAT3(0.5f, -0.5f, 0.5f), dx::XMFLOAT2(0.0f, 2.0f / 4.0f)}, // Haut droite
		{dx::XMFLOAT3(0.5f, -0.5f, -0.5f), dx::XMFLOAT2(bas, 2.0f / 4.0f)}, // Bas droite
		{dx::XMFLOAT3(-0.5f, -0.5f, -0.5f), dx::XMFLOAT2(bas, 1.0f / 4.0)} // Bas gauche
	};

	std::vector<unsigned short> indices = {
		// Face avant
		0, 1, 2,  0, 2, 3,

		// Face arrière
		4, 6, 5,  4, 7, 6,

		// Face gauche
		8, 9, 10,  8, 10, 11,

		// Face droite
		12, 14, 13,  12, 15, 14,

		// Face haut
		16, 17, 18,  16, 18, 19,

		// Face bas
		20, 22, 21,  20, 23, 22
	};


	this->addBindable(std::make_unique<VertexBuffer>(renderer, vertices));
	this->addIndexBuffer(std::make_unique<IndexBuffer>(renderer, indices));

	auto pvs = std::make_unique<VertexShader>(renderer, L"textureVS");
	auto pvsbc = pvs->getBytecode();
	this->addBindable(std::move(pvs));

	this->addBindable(std::make_unique<PixelShader>(renderer, L"texturePS"));
	//the layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	this->addBindable(std::make_unique<InputLayout>(renderer, inputElementDesc, pvsbc));

	// Bind the texture
	this->addBindable(std::make_unique<Texture>(renderer, *pImage));
	this->addBindable(std::make_unique<SamplerState>(renderer));
}
