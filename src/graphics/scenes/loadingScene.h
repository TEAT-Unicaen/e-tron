#pragma once

#include "scene.h"
#include "../objects/basicObjects/basicObjects.h"

class LoadingScene : public Scene {
public:
	LoadingScene(Renderer& renderer, std::string name);
	void onLoad() override;
	void update(float deltaTime) override;
	void handleInput(Window& wnd) override;
};