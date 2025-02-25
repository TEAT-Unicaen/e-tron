#pragma once

#include "../objects/drawable.h"
#include "../objects/bindable/bindableBase.h"

class BasicMotorcycle : public Drawable {
public:
	BasicMotorcycle(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 9>& colors);
protected:
	std::array<Color, 9> colors;
};