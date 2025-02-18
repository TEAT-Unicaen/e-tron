#include "cube.h"

Cube::Cube(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity)
	: position(startPosition), rotation(startRotation), velocity(velocity), angularVelocity(angularVelocity) {
	
	struct Vertex {
		dx::XMFLOAT3 pos;
	};

	// set all the verticies of the cube
	const std::vector<Vertex> verticies = {
		{{-1.0f, -1.0f, -1.0f}},
		{{1.0f, -1.0f, -1.0f}},
		{{-1.0f, 1.0f, -1.0f}},
		{{1.0f, 1.0f, -1.0f}},
		{{-1.0f, -1.0f, 1.0f}},
		{{1.0f, -1.0f, 1.0f}},
		{{-1.0f, 1.0f, 1.0f}},
		{{1.0f, 1.0f, 1.0f}}
	};

	this->addBindable(std::make_unique<VertexBuffer>(renderer, verticies));
	auto pvs = std::make_unique<VertexShader>(renderer, L"shaders/vertexShader.cso");
	auto pvsbc = pvs->getBytecode();
	this->addBindable(std::move(pvs));

	this->addBindable(std::make_unique<PixelShader>(renderer, L"shaders/pixelShader.cso"));

	// Select the indices of the verticies that make up each face
	const std::vector<unsigned short> indices =
	{
		0, 2, 1, 2, 3, 1,
		1, 3, 5, 3, 7, 5,
		2, 6, 3, 3, 6, 7,
		4, 5, 7, 4, 7, 6,
		0, 4, 2, 2, 4, 6,
		0, 1, 4, 1, 5, 4
	};

	this->addIndexBuffer(std::make_unique<IndexBuffer>(renderer, indices));

	// Have each face be a different color
	struct ConstantBufferColor {
		struct {
			dx::XMFLOAT3 color;
			float padding;
		} colorFaces[6];
	};

	const ConstantBufferColor colorBuffer =
	{
		{
			{ {1.0f,0.0f,1.0f} },
			{ {1.0f,0.0f,0.0f} },
			{ {0.0f,1.0f,0.0f} },
			{ {0.0f,0.0f,1.0f} },
			{ {1.0f,1.0f,0.0f} },
			{ {0.0f,1.0f,1.0f} },
		}
	};
	this->addBindable(std::make_unique<PixelConstantBuffer<ConstantBufferColor>>(renderer, colorBuffer));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	this->addBindable(std::make_unique<InputLayout>(renderer, ied, pvsbc));
	this->addBindable(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	this->addBindable(std::make_unique<TransformConstantBuffer>(renderer, *this));
}

void Cube::update(float delta) noexcept {
	// Translation
	this->position.x += this->velocity.x * delta;
	this->position.y += this->velocity.y * delta;
	this->position.z += this->velocity.z * delta;

	// Rotation
	this->rotation.x += this->angularVelocity.x * delta;
	this->rotation.y += this->angularVelocity.y * delta;
	this->rotation.z += this->angularVelocity.z * delta;
}

// Returns the transformation matrix for the cube
dx::XMMATRIX Cube::getTransform() const {
	return dx::XMMatrixRotationRollPitchYaw(this->rotation.x, this->rotation.y, this->rotation.z) *
			dx::XMMatrixTranslation(this->position.x, this->position.y, this->position.z);
}
