#include "coloredCube.h"

ColoredCube::ColoredCube(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 6> &colors)
	: Cube(renderer, startPosition, startRotation, velocity, angularVelocity), colors(colors) {


    const std::vector<dx::XMFLOAT3> vertices = {
        dx::XMFLOAT3(-0.5f, -0.5f, -0.5f),
        dx::XMFLOAT3(0.5f, -0.5f, -0.5f),
        dx::XMFLOAT3(-0.5f, 0.5f, -0.5f),
        dx::XMFLOAT3(0.5f, 0.5f, -0.5f),
        dx::XMFLOAT3(-0.5f, -0.5f, 0.5f),
        dx::XMFLOAT3(0.5f, -0.5f, 0.5f),
        dx::XMFLOAT3(-0.5f, 0.5f, 0.5f),
        dx::XMFLOAT3(0.5f, 0.5f, 0.5f)
    };
	this->addBindable(std::make_unique<VertexBuffer>(renderer, vertices));
	
	const std::vector<unsigned short> indices = {
		0, 2, 1,    2, 3, 1, // Front face
		1, 3, 5,    3, 7, 5, // Back face
		5, 7, 4,    7, 6, 4, // Right face
		4, 6, 0,    6, 2, 0, // Left face
		2, 6, 3,    6, 7, 3, // Top face
		4, 0, 5,    5, 0, 1 // Bottom face
	};
	this->addIndexBuffer(std::make_unique<IndexBuffer>(renderer, indices));

	auto pvs = std::make_unique<VertexShader>(renderer, L"defaultVS");
	auto pvsbc = pvs->getBytecode();
	this->addBindable(std::move(pvs));

	this->addBindable(std::make_unique<PixelShader>(renderer, L"coloredCubePS"));

	struct ColorBuffer {
		dx::XMFLOAT4 colors[6];
	};

	const ColorBuffer cb = {
		{
			this->colors[0].toFloat4(),
			this->colors[1].toFloat4(),
			this->colors[2].toFloat4(),
			this->colors[3].toFloat4(),
			this->colors[4].toFloat4(),
			this->colors[5].toFloat4()
		}
	};
	this->addBindable(std::make_unique<PixelConstantBuffer<ColorBuffer>>(renderer, cb, 0u));

	//the layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	this->addBindable(std::make_unique<InputLayout>(renderer, inputElementDesc, pvsbc));
}