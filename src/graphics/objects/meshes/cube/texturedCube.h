#pragma once

#include "cube.h"

class TexturedCube : public Cube {
public:
	TexturedCube(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::shared_ptr<Image> pImage);
private:
	std::shared_ptr<Image> pImage;
};