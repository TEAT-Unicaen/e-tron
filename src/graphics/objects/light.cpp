#include "light.h"

Light::Light(Renderer& renderer, const dx::XMFLOAT3& pos, const Color color)
	: position(pos), color(color),
	lightBufferData(LightBuffer{
		pos,
		color.toFloat3(),
		10.0f,
		1.0f,
		0.045f,
		0.0075f
	}) {

	this->pObj = std::make_unique<SingleMeshDrawable>(
		renderer,
		pos,
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		Drawable::getMesh("sphere"),
		L"defaultVS",
		L"coloredSpherePS",
		color
	);
	pObj->setScale(dx::XMFLOAT3{ 0.1f, 0.1f, 0.1f });
}

void Light::draw(Renderer& renderer) {
	this->pObj->setPosition(this->position);
	this->pObj->draw(renderer);
}

Light::LightBuffer Light::getLightBufferData() const noexcept {
	return lightBufferData;
}

void Light::setPosition(const dx::XMFLOAT3& pos) noexcept {
	this->position = pos;
	this->lightBufferData.position = pos;
}

void Light::setColor(Renderer& renderer, const Color color) noexcept {
	this->color = color;
	this->lightBufferData.color = color.toFloat3();
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
