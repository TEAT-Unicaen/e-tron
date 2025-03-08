#include "coloredSphere.h"

ColoredSphere::ColoredSphere(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 1>& colors)
	: Sphere(renderer, startPosition, startRotation, velocity, angularVelocity), colors(colors) {

	struct Vertex {
		dx::XMFLOAT3 position;
	};

	float radius = 0.5f;
	UINT slices = 40u;
	UINT stacks = 40u;

	std::vector<Vertex> vertices;
	vertices.reserve((slices + 1)* (stacks + 1));
	for (UINT i = 0; i <= stacks; i++) {
		float phi = dx::XM_PI * i / stacks;  // Fix: Full latitude range [0, π]
		for (UINT j = 0; j <= slices; j++) {
			float theta = 2.0f * dx::XM_PI * j / slices;
			vertices.push_back({
				{
					radius * std::sin(phi) * std::cos(theta),
					radius * std::cos(phi),
					radius * std::sin(phi) * std::sin(theta)
				}
				});
		}
	}

	// Generate indices
	std::vector<unsigned short> indices;
	indices.reserve(slices * stacks * 6);
	for (UINT i = 0; i < stacks; i++) {
		for (UINT j = 0; j < slices; j++) {
			unsigned short topLeft = i * (slices + 1) + j;
			unsigned short bottomLeft = (i + 1) * (slices + 1) + j;
			unsigned short topRight = i * (slices + 1) + j + 1;
			unsigned short bottomRight = (i + 1) * (slices + 1) + j + 1;

			// First Triangle
			indices.push_back(topLeft);
			indices.push_back(topRight);
			indices.push_back(bottomLeft);
			

			// Second Triangle
			indices.push_back(topRight);
			indices.push_back(bottomRight);
			indices.push_back(bottomLeft);
			
		}
	}

	this->addBindable(std::make_shared<VertexBuffer>(renderer, vertices));
	this->addBindable(std::make_shared<IndexBuffer>(renderer, indices));

	auto pvs = shaderManager.getVertexShader(L"defaultVS");
	auto pvsbc = pvs->getBytecode();
	this->addBindable(std::move(pvs));
	this->addBindable(shaderManager.getPixelShader(L"coloredSpherePS"));
	struct ColorBuffer {
		dx::XMFLOAT4 colors[1];
	};
	const ColorBuffer cb = {
		{
			this->colors[0].toFloat4()
		}
	};
	this->addBindable(std::make_shared<PixelConstantBuffer<ColorBuffer>>(renderer, cb, 0u));
	const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	this->addBindable(std::make_shared<InputLayout>(renderer, inputElementDesc, pvsbc));
}