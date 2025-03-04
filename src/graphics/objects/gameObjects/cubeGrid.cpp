#include "cubeGrid.h"  

CubeGrid::CubeGrid(
	Renderer& renderer,
	dx::XMFLOAT3 startPosition,
	dx::XMFLOAT3 startRotation,
	dx::XMFLOAT3 velocity,
	dx::XMFLOAT3 angularVelocity,
	std::array<Color, 6> pImage,
	unsigned int longueur,
	unsigned int largeur) {

	float longCenter = static_cast<float>(longueur) / 2;
	float largCenter = static_cast<float>(largeur) / 2;

	for (int i = 0; i < longueur; i++) {
		for (int y = 0; y < largeur; y++) {
			this->add(std::make_unique<ColoredCube>(
				renderer,
				dx::XMFLOAT3{ i - longCenter, 0.0f, y - largCenter },
				dx::XMFLOAT3{ i * dx::XM_PI, y * dx::XM_PI, y * dx::XM_PI },
				velocity,
				angularVelocity,
				pImage
			));
		}
	}

}