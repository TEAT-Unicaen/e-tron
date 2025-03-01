#pragma once

#include "object.h"
#include "basicObjects/tore/coloredTore.h"

class DoubleTore : public Object {
public:
	DoubleTore(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 1> colors);
};