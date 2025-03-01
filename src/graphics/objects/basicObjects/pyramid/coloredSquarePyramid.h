#pragma once

#include "squarePyramid.h"

class ColoredSquarePyramid : public SquarePyramid {
public:
	ColoredSquarePyramid(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 5> colors);
protected:
	std::array<Color, 5> colors;
};