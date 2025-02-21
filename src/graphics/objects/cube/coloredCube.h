#pragma once

#include "cube.h"

class ColoredCube : public Cube {
public:
	ColoredCube(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 6> &colors);
private:
	std::array<Color, 6> colors;
};