#include "squarePyramid.h"

SquarePyramid::SquarePyramid(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity)
	: Drawable(renderer, startPosition, startRotation, velocity, angularVelocity) {
	this->addBindable(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	this->addBindable(std::make_unique<TransformConstantBuffer>(renderer, *this));
}
