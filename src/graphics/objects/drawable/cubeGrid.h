#pragma once

#include "object.h"
#include "../meshes/cube/texturedCube.h"
#include "../meshes/cube/coloredCube.h"

class CubeGrid : public Object {
public:
	CubeGrid(
		Renderer& renderer,
		dx::XMFLOAT3 startPosition,
		dx::XMFLOAT3 startRotation,
		dx::XMFLOAT3 velocity,
		dx::XMFLOAT3 angularVelocity,
		std::array<Color, 6> pImage,
		unsigned int longueur,
		unsigned int largeur);
};