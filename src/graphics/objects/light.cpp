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

	this->pObj = std::make_unique<SingleMeshDrawable>(
		renderer,
		pos,
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		Drawable::getMesh("sphere"),
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

void Light::setPosition(const dx::XMFLOAT3& pos) noexcept {
	this->position = pos;
}

void Light::setColor(Renderer& renderer, const Color color) noexcept {
	this->color = color;
	this->pObj.release();
	this->pObj = std::make_unique<SingleMeshDrawable>(
		renderer,
		this->position,
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		Drawable::getMesh("sphere"),
		L"defaultVS",
		L"coloredSpherePS",
		color
	);
}

dx::XMFLOAT3 Light::getPosition() const noexcept {
	return this->position;
}

Color Light::getColor() const noexcept {
	return this->color;
}
