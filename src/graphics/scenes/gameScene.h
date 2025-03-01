#pragma once

#include "scene.h"

#include <random>

class GameScene : public Scene {
public:
	GameScene(Renderer& renderer, std::string name);

	void onLoad() override;

	void update(float deltaTime) override;
	void handleInput(Window& wnd) override;

private:
	bool isPaused = false;
};