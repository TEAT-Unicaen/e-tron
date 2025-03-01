#pragma once

#include "tore.h"

class ColoredTore : public Tore {
public:
	ColoredTore(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 1>& colors);
private:
	std::array<Color, 1> color;
};