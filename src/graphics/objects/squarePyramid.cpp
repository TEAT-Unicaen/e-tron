#include "squarePyramid.h"

SquarePyramid::SquarePyramid(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity)
	: position(startPosition), rotation(startRotation), velocity(velocity), angularVelocity(angularVelocity) {
	struct Vertex {
		dx::XMFLOAT3 pos;
		dx::XMFLOAT2 tex;// uv
	};
	/*
	 *     0.0f     1.0f
	 * u : left to right
	 * v : top to bottom
	 */
	// vertices

	const dx::XMFLOAT2 BG = { 0.4f, 0.33f };
	const dx::XMFLOAT2 BD = { 0.666f, 0.33f };
	const dx::XMFLOAT2 HD = { 0.4f, 0.66f };
	const dx::XMFLOAT2 HG = { 0.666f, 0.66f };

	std::vector<Vertex> vertices = {
		// Base (carré en bas)
		{{-0.5f, 0.0f, -0.5f}, BG}, // 0 - Bas-gauche
		{{ 0.5f, 0.0f, -0.5f}, BD}, // 1 - Bas-droit
		{{ 0.5f, 0.0f,  0.5f}, HD }, // 2 - Haut-droit
		{{-0.5f, 0.0f,  0.5f}, HG}, // 3 - Haut-gauche

		// Face avant
		{{ -0.5f, 0.0f, -0.5f }, BG}, // 4 - Bas-gauche
		{{ 0.0f, 1.0f,  0.0f }, {0.5f, 0.0f}},  // 5 - Pointe
		{{ 0.5f, 0.0f, -0.5f}, BD}, // 6 - Bas-droit

		// Face droite
		{{ 0.5f, 0.0f, -0.5f}, BD}, // 7 - Bas-droit
		{{ 0.0f, 1.0f,  0.0f }, {1.0f, 0.5f}},  // 8 - Pointe
		{{ 0.5f, 0.0f,  0.5f}, { 0.666f, 0.66f }}, // 9 - Haut-droit

		// Face arrière
		{{ 0.5f, 0.0f,  0.5f}, HD}, // 10 - Haut-droit
		{{ 0.0f, 1.0f,  0.0f }, {0.5f, 0.9f}},  // 11 - Pointe
		{{ -0.5f, 0.0f,  0.5f}, HG}, // 12 - Haut-gauche

		// Face gauche
		{{ -0.5f, 0.0f,  0.5f}, { 0.33f, 0.66f }}, // 13 - Haut-gauche
		{{ 0.0f, 1.0f,  0.0f }, {0.01f, 0.5f}},  // 14 - Pointe
		{{ -0.5f, 0.0f, -0.5f}, { 0.33f, 0.4f }} // 15 - Bas-gauche
	};


	this->addBindable(std::make_unique<Texture>(renderer, Image(L"..\\..\\..\\assets\\img\\obamium.png")));
	this->addBindable(std::make_unique<SamplerState>(renderer));

	this->addBindable(std::make_unique<VertexBuffer>(renderer, vertices));

	auto pvs = std::make_unique<VertexShader>(renderer, L"shaders/textureVS.cso");
	auto pvsbc = pvs->getBytecode();
	this->addBindable(std::move(pvs));

	this->addBindable(std::make_unique<PixelShader>(renderer, L"shaders/texturePS.cso"));

	// Select the indices of the verticies that make up each face
std::vector<unsigned short> indices = {
    // Base (2 triangles)
    0, 1, 2,  
    0, 2, 3,  

	// Face avant
	4, 5, 6,

	// Face droite
	7, 8, 9,

	// Face arrière
	10, 11, 12,

	// Face gauche
	13, 14, 15
};



	this->addIndexBuffer(std::make_unique<IndexBuffer>(renderer, indices));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	this->addBindable(std::make_unique<InputLayout>(renderer, ied, pvsbc));
	this->addBindable(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	this->addBindable(std::make_unique<TransformConstantBuffer>(renderer, *this));
}

void SquarePyramid::update(float delta) noexcept {
	// Translation
	this->position.x += this->velocity.x * delta;
	this->position.y += this->velocity.y * delta;
	this->position.z += this->velocity.z * delta;

	// Rotation
	this->rotation.x += this->angularVelocity.x * delta;
	this->rotation.y += this->angularVelocity.y * delta;
	this->rotation.z += this->angularVelocity.z * delta;
}

dx::XMMATRIX SquarePyramid::getTransform() const {
	return dx::XMMatrixRotationRollPitchYaw(this->rotation.x, this->rotation.y, this->rotation.z) *
		dx::XMMatrixTranslation(this->position.x, this->position.y, this->position.z);
}