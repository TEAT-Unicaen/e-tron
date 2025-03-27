#include "grid3D.h"

Grid3D::Grid3D(Renderer& renderer, UINT lenght, UINT width, Mesh& mesh)
	: InstancedMeshDrawable(
		renderer,
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		mesh,
		L"instancePhongVS",
		L"instancePhongPS"
	),
	lenght(lenght),
	width(width) {
	int lenghtMiddle = lenght / 2;
	int widthMiddle = width / 2;
	this->pInstanceBuffer->setMaxInstances(renderer, lenght * width);

	for (int i = 0; i < lenght ; i++) {
		for (int j = 0 ; j < width ; j++) {
			this->pInstanceBuffer->addInstance(
				renderer,
				dx::XMFLOAT3(static_cast<float>(i), 0.0f, static_cast<float>(j)),
				dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
				(i + j) % 2 ? Color::WHITE : Color::DARK_GRAY
			);
		}
	}
}