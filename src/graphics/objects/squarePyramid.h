#pragma once

#include "drawable.h"
#include "bindable/bindableBase.h"
#include "bindable/texture.h"
#include "bindable/samplerState.h"

class SquarePyramid : public Drawable {
public:
	SquarePyramid(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity);
	void update(float delta) noexcept override;
	dx::XMMATRIX getTransform() const override;
private:
	dx::XMFLOAT3 position = { 0.0f, 0.0f, 0.0f };
	dx::XMFLOAT3 rotation = { 0.0f, 0.0f, 0.0f };
	dx::XMFLOAT3 velocity = { 0.0f, 0.0f, 0.0f };
	dx::XMFLOAT3 angularVelocity = { 0.0f, 0.0f, 0.0f };
};