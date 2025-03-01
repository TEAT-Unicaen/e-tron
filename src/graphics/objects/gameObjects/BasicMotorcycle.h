#pragma once

#include "../basicObjects/drawable.h"
#include "../basicObjects/bindable/bindableBase.h"

class BasicMotorcycle : public Drawable {
public:
	BasicMotorcycle(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 9>& colors);
protected:
	std::array<Color, 9> colors;
};