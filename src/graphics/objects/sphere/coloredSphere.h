#pragma once

#include "sphere.h"

class ColoredSphere : public Sphere {
public:
	ColoredSphere(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 1>& colors);
private:
	std::array<Color, 1> colors;
};