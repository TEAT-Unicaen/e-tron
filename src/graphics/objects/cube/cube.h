#pragma once

#include "../drawable.h"
#include "../bindable/bindableBase.h"

class Cube : public Drawable {
public:
	Cube(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity);
	void update(float delta) noexcept override;
	dx::XMMATRIX getTransform() const override;
};