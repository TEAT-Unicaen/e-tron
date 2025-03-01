#include "coloredTore.h"

ColoredTore::ColoredTore(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 1>& color)
	: Tore(renderer, startPosition, startRotation, velocity, angularVelocity), color(color) {


	this->addBindable(std::make_unique<PixelShader>(renderer, L"coloredSpherePS"));
	struct ColorBuffer {
		dx::XMFLOAT4 colors[1];
	};
	const ColorBuffer cb = {
		{
			this->color[0].toFloat4()
		}
	};
	this->addBindable(std::make_unique<PixelConstantBuffer<ColorBuffer>>(renderer, cb, 0u));
}