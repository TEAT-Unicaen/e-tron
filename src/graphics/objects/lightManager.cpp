#include "lightManager.h"

LightManager::LightManager(Renderer& renderer)
	: lightsBuffer(PixelStructuredBuffer<Light::LightBuffer>(renderer, 10u, 1u)) {
	this->pLights.reserve(10);
}

void LightManager::drawAll(Renderer& renderer) {
	for (auto& light : this->pLights)
		light->draw(renderer);
}

void LightManager::bindAll(Renderer& renderer) {
	this->updateBuffer(renderer);
	this->lightsBuffer.bind(renderer);
}

void LightManager::addLight(const std::shared_ptr<Light>& light) {
	this->pLights.emplace_back(light);
	this->needToUpdateBuffer = true;
}

void LightManager::addLight(Renderer& renderer, const dx::XMFLOAT3& pos, const Color color) {
	std::shared_ptr<Light> pLight = std::make_shared<Light>(renderer, pos, color);
	this->addLight(pLight);
}

std::shared_ptr<Light>& LightManager::getLight(size_t index) {
	return this->pLights[index];
}

void LightManager::updateBuffer(Renderer& renderer) {
	std::vector<Light::LightBuffer> lightData;
	lightData.reserve(this->pLights.size());
	for (auto& light : this->pLights)
		lightData.push_back(light->getLightBufferData());
	this->lightsBuffer.update(renderer, lightData);
	this->needToUpdateBuffer = false;
}