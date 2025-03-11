#include "grid3D.h"

Grid3D::Grid3D(Renderer& renderer, UINT lenght, UINT width, Mesh& mesh)
	: InstancedMeshDrawable(
		renderer,
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		mesh,
		L"instancePhongVS",
		L"phongPS",
		Color::WHITE
	),
	lenght(lenght),
	width(width),
	mesh(mesh)
{
	for (UINT i = 0; i < lenght; i++) {
		for (UINT j = 0; j < width; j++) {
			this->addInstance(
				renderer,
				dx::XMFLOAT3(static_cast<float>(i), 0.0f, static_cast<float>(j)),
				dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
				mesh,
				L"instancePhongVS",
				L"phongPS",
				Color::WHITE
			);
		}
	}
	



}