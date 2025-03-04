#pragma once

#include "scene.h"
#include "../objects/gameObjects/cubeGrid.h"
#include "../objects/gameObjects/motorPlayer.h"

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