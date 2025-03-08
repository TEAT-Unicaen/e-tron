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
		{dx::XMFLOAT3(-0.5f, 0.5f, -0.5f), dx::XMFLOAT2(haut, 1.0f / 4.0f)}, //0
		{dx::XMFLOAT3(0.5f, 0.5f, -0.5f), dx::XMFLOAT2(haut, 2.0f / 4.0f)}, //1
		{dx::XMFLOAT3(0.5f, -0.5f, -0.5f), dx::XMFLOAT2(bas, 2.0f / 4.0f)}, //2
		{dx::XMFLOAT3(-0.5f, -0.5f, -0.5f), dx::XMFLOAT2(bas, 1.0f / 4.0f)}, //3

		// Face arrière
		{dx::XMFLOAT3(-0.5f, 0.5f, 0.5f), dx::XMFLOAT2(haut, 1.0f)}, //4
		{dx::XMFLOAT3(0.5f, 0.5f, 0.5f), dx::XMFLOAT2(haut, 3.0f / 4.0f)}, //5
		{dx::XMFLOAT3(0.5f, -0.5f, 0.5f), dx::XMFLOAT2(bas, 3.0f / 4.0f)}, //6
		{dx::XMFLOAT3(-0.5f, -0.5f, 0.5f), dx::XMFLOAT2(bas, 1.0f)}, //7

		// Face gauche
		{dx::XMFLOAT3(-0.5f, 0.5f, 0.5f), dx::XMFLOAT2(haut, 0.0f)}, //8
		{dx::XMFLOAT3(-0.5f, -0.5f, 0.5f), dx::XMFLOAT2(bas, 0.0f)}, //9

		// Face haut
		{dx::XMFLOAT3(-0.5f, 0.5f, 0.5f), dx::XMFLOAT2(1.0f, 1.0f / 4.0)}, //10
		{dx::XMFLOAT3(0.5f, 0.5f, 0.5f), dx::XMFLOAT2(1.0f, 2.0f / 4.0f)}, //11

		// Face bas
		{dx::XMFLOAT3(-0.5f, -0.5f, 0.5f), dx::XMFLOAT2(0.0f, 1.0f / 4.0)}, //12
		{dx::XMFLOAT3(0.5f, -0.5f, 0.5f), dx::XMFLOAT2(0.0f, 2.0f / 4.0f)}, //13
	};

	std::vector<unsigned short> indices = {
		// Face avant
		0, 1, 2,  0, 2, 3,

		// Face arrière
		4, 6, 5,  4, 7, 6,

		// Face gauche
		8, 0, 3,  8, 3, 9,

		// Face droite
		5, 2, 1,  5, 6, 2,

		// Face haut
		10, 11, 1,  10, 1, 0,

		// Face bas
		12, 2, 13,  12, 3, 2
	};


	this->addBindable(std::make_shared<VertexBuffer>(renderer, vertices));
	this->addBindable(std::make_shared<IndexBuffer>(renderer, indices));

	// Shader
	auto pvs = shaderManager.getVertexShader(L"textureVS");
	auto pvsbc = pvs->getBytecode();
	this->addBindable(std::move(pvs));

	this->addBindable(shaderManager.getVertexShader(L"texturePS"));
	//the layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	this->addBindable(std::make_shared<InputLayout>(renderer, inputElementDesc, pvsbc));

	// Bind the texture
	this->addBindable(std::make_shared<Texture>(renderer, *pImage));
	this->addBindable(std::make_shared<SamplerState>(renderer));
}
