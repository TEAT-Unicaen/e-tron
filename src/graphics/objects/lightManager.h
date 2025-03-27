#pragma once

#include "../core/render/renderer.h"
#include "bindable/buffers/structuredBuffer/pixelStructuredBuffer.h"
#include "light.h"

class LightManager {
public:
	LightManager(Renderer& renderer);
	~LightManager() = default;
	
	void drawAll(Renderer& renderer);
	void bindAll(Renderer& renderer);

	void addLight(const std::shared_ptr<Light>& light);
	void addLight(Renderer& renderer, const dx::XMFLOAT3& pos, const Color color);

	std::shared_ptr<Light>& getLight(size_t index);
private:
	void updateBuffer(Renderer& renderer);
	bool needToUpdateBuffer = false;
	std::vector<std::shared_ptr<Light>> pLights;
	PixelStructuredBuffer<Light::LightBuffer> lightsBuffer;
};