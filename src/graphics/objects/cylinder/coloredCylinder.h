#pragma once

#include "cylinder.h"

class ColoredCylinder : public Cylinder {
public:
    ColoredCylinder(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 3>& colors);
private:
    std::array<Color, 3> colors;
};
