#include "BasicMotorcycle.h"

BasicMotorcycle::BasicMotorcycle(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 9>& colors)
	: Drawable(renderer, startPosition, startRotation, velocity, angularVelocity), colors(colors) {

	this->addBindable(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	this->addBindable(std::make_unique<TransformConstantBuffer>(renderer, *this));

	const std::vector<dx::XMFLOAT3> vertices = {
		// Le centre de l'objet se situe entre le cube et la pyramide, au milieu de la forme
		dx::XMFLOAT3(0.0f, 0.0f, 1.0f), // Pointe de l'avant

		dx::XMFLOAT3(-0.5f, -0.5f, 0.0f), // centre haut gauche
		dx::XMFLOAT3(0.5f, -0.5f, 0.0f), // centre haut droit
		dx::XMFLOAT3(-0.5f, 0.5f, 0.0f), // centre bas gauche
		dx::XMFLOAT3(0.5f, 0.5f, 0.0f), // centre bas droit

		dx::XMFLOAT3(-0.5f, -0.5f, -1.0f), // arrière haut gauche
		dx::XMFLOAT3(0.5f, -0.5f, -1.0f), // arrière haut droit
		dx::XMFLOAT3(-0.5f, 0.5f, -1.0f), // arrière bas gauche
		dx::XMFLOAT3(0.5f, 0.5f, -1.0f), // arrière bas droit
	};
	this->addBindable(std::make_unique<VertexBuffer>(renderer, vertices));

	const std::vector<unsigned short> indices = {
		// Pyramide avant
		0, 1, 2,				// Face du haut
		0, 3, 1,				// Face de gauche
		0, 2, 4,				// Face de droite
		0, 4, 3,				// Face du bas

		// Cube cotés
		1, 6, 2,	1, 5, 6,	// Face du haut
		1, 3, 7,	1, 7, 5,	// Face de gauche
		2, 8, 4,	2, 6, 8,	// Face de droite
		3, 4, 8,	3, 8, 7,	// Face du bas
		
		// Cube arrière
		5, 7, 6,	6, 7, 8		// Face arrière

	};
	this->addIndexBuffer(std::make_unique<IndexBuffer>(renderer, indices));

	auto pvs = std::make_unique<VertexShader>(renderer, L"defaultVS");
	auto pvsbc = pvs->getBytecode();
	this->addBindable(std::move(pvs));

	this->addBindable(std::make_unique<PixelShader>(renderer, L"coloredMotorcyclePS"));

	struct ColorBuffer {
		dx::XMFLOAT4 colors[9];
	};

	const ColorBuffer cb = {
		{
			this->colors[0].toFloat4(),
			this->colors[1].toFloat4(),
			this->colors[2].toFloat4(),
			this->colors[3].toFloat4(),
			this->colors[4].toFloat4(),
			this->colors[5].toFloat4(),
			this->colors[6].toFloat4(),
			this->colors[7].toFloat4(),
			this->colors[8].toFloat4(),
		}
	};
	this->addBindable(std::make_unique<PixelConstantBuffer<ColorBuffer>>(renderer, cb, 0u));

	//the layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	this->addBindable(std::make_unique<InputLayout>(renderer, inputElementDesc, pvsbc));
}