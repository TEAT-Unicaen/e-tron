#pragma once

#include "cylinderTruncated.h"

class ColoredCylinderTruncated : public CylinderTruncated {
public:
    ColoredCylinderTruncated(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 3>& colors);
private:
    std::array<Color, 3> colors;
};
