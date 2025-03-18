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

	for (int i = -lenghtMiddle; i < lenghtMiddle ; i++) {
		for (int j = -widthMiddle ; j < widthMiddle ; j++) {
			this->pInstanceBuffer->addInstance(
				renderer,
				dx::XMFLOAT3(static_cast<float>(i), 0.0f, static_cast<float>(j)),
				dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
				(i + j) % 2 ? Color::WHITE : Color::BLACK
			);
		}
	}
}