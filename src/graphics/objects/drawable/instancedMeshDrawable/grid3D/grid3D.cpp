#include "grid3D.h"

Grid3D::Grid3D(Renderer& renderer, UINT lenght, UINT width, Mesh& mesh)
	: InstancedMeshDrawable(
		renderer,
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		mesh,
		L"instanceVS",
		L"coloredCubePS",
		std::vector<Color> {
		Color::RED,
		Color::GREEN,
		Color::BLUE,
		Color::MAGENTA,
		Color::CYAN,
		Color::YELLOW
		}
	),
	lenght(lenght),
	width(width),
	mesh(mesh)
{
	int lenghtMiddle = lenght / 2;
	int widthMiddle = width / 2;

	for (int i = -lenghtMiddle; i < lenghtMiddle ; i++) {
		for (int j = -widthMiddle ; j < widthMiddle ; j++) {
			this->addInstance(
				renderer,
				dx::XMFLOAT3(static_cast<float>(i), 0.0f, static_cast<float>(j)),
				dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
				dx::XMFLOAT3(1.0f, 1.0f, 1.0f)
			);
		}
	}
	



}