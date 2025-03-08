#pragma once

#include "object.h"
#include "../meshes/cylinder/coloredcylinderTruncated.h"

class MotorPlayer : public Object {
public:
	MotorPlayer(
		Renderer& renderer,
		dx::XMFLOAT3 startPosition,
		dx::XMFLOAT3 startRotation,
		dx::XMFLOAT3 velocity,
		dx::XMFLOAT3 angularVelocity,
		std::array<Color, 3> wheelColor);
};