#include "motorPlayer.h"  

MotorPlayer::MotorPlayer(
	Renderer& renderer,
	dx::XMFLOAT3 startPosition,
	dx::XMFLOAT3 startRotation,
	dx::XMFLOAT3 velocity,
	dx::XMFLOAT3 angularVelocity,
	std::array<Color, 3> wheelColor) {

	for (int i = -1; i < 2; i+=2) {
		this->add(std::make_unique<ColoredCylinderTruncated>(
			renderer,
			dx::XMFLOAT3{ static_cast<float>(i), 2.0f, 0.0f },
			dx::XMFLOAT3{ 2*dx::XM_PI, 0.0f, 0.0f },	// PI dosn't work
			velocity,
			angularVelocity,
			wheelColor
		));
	}
}