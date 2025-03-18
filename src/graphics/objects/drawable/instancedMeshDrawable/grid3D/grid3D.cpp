#include "grid3D.h"

Grid3D::Grid3D(Renderer& renderer, UINT lenght, UINT width, Mesh& mesh)
	: InstancedMeshDrawable(
		renderer,
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		mesh,
		L"gridPhongVS",
		L"gridPhongPS",
		std::vector<Color> {
			Color::BLACK,
			Color::WHITE
		}
	),
	lenght(lenght),
	width(width),
	mesh(mesh) {
	// PS constant buffer
	struct InstanceInfo {
		UINT lenght;
		UINT width;
		float padding[2];
	};
	InstanceInfo cb = {};
	cb.lenght = lenght;
	cb.width = width;
	this->addBindable(std::make_shared<PixelConstantBuffer<InstanceInfo>>(renderer, cb, 2u));

	int lenghtMiddle = lenght / 2;
	int widthMiddle = width / 2;
	this->pInstanceBuffer->setMaxInstances(renderer, lenght * width);
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