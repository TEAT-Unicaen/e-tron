#include "light.h"

Light::Light(Renderer& renderer, const dx::XMFLOAT3& pos, const Color color)
	: position(pos), color(color),
	lightBufferData(LightBuffer{
		pos,
		color.toFloat3(),
		dx::XMFLOAT3{0.4f, 0.4f, 0.4f},
		1.0f,
		1.0f,
		0.045f,
		0.0075f
	}),
	lightBuffer(PixelConstantBuffer<LightBuffer>(
		renderer,
		this->lightBufferData,
		1u
	)) {


	Mesh mesh = Sphere(renderer);

	this->pObj = std::make_unique<SingleMeshDrawable>(
		renderer,
		pos,
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		mesh,
		L"defaultVS",
		L"coloredSpherePS",
		color
	);
}

void Light::draw(Renderer& renderer) {
	this->pObj->setPosition(this->position);
	this->pObj->draw(renderer);
}

void Light::bind(Renderer& renderer) {
	this->lightBufferData.position = this->position;

	this->lightBufferData.color = this->color.toFloat3();

	this->lightBuffer.update(renderer, this->lightBufferData);
	this->lightBuffer.bind(renderer);
}