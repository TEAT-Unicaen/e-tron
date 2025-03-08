#pragma once

#include "../../drawable/drawable.h"
#include "../../bindable/bindableBase.h"

class Tore : public Drawable {
public:
	Tore(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity);
};