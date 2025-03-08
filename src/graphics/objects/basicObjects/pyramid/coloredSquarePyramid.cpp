#include "coloredSquarePyramid.h"

ColoredSquarePyramid::ColoredSquarePyramid(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 5> colors)
	: SquarePyramid(renderer, startPosition, startRotation, velocity, angularVelocity), colors(colors) {

	std::vector<dx::XMFLOAT3> vertices = {
		// Base
		dx::XMFLOAT3(-0.5f, -0.5f, -0.5f), //0
		dx::XMFLOAT3(0.5f, -0.5f, -0.5f), //1
		dx::XMFLOAT3(0.5f, -0.5f, 0.5f), //2
		dx::XMFLOAT3(-0.5f, -0.5f, 0.5f), //3

		// Sommet
		dx::XMFLOAT3(0.0f, 0.5f, 0.0f), //4
	};
	std::vector<unsigned short> indices = {
		// Base
		0, 1, 2,   0, 2, 3,
		// Faces
		0, 4, 1, // Front face
		1, 4, 2, // Right face
		2, 4, 3, // Back face
		3, 4, 0, // Left face
	};
	this->addBindable(std::make_shared<VertexBuffer>(renderer, vertices));
	this->addBindable(std::make_shared<IndexBuffer>(renderer, indices));

	auto pvs = shaderManager.getVertexShader(L"defaultVS");
	auto pvsbc = pvs->getBytecode();
	this->addBindable(std::move(pvs));

	this->addBindable(shaderManager.getPixelShader(L"coloredSquarePyramidPS"));

	struct ColorBuffer {
		dx::XMFLOAT4 colors[5];
	};

	const ColorBuffer cb = {
		{
			this->colors[0].toFloat4(),
			this->colors[1].toFloat4(),
			this->colors[2].toFloat4(),
			this->colors[3].toFloat4(),
			this->colors[4].toFloat4()
		}
	};
	this->addBindable(std::make_shared<PixelConstantBuffer<ColorBuffer>>(renderer, cb, 0u));

	//the layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	this->addBindable(std::make_shared<InputLayout>(renderer, inputElementDesc, pvsbc));
}