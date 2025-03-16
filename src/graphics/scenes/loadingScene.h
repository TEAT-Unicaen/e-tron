#pragma once

#include "scene.h"
#include "../objects/meshes/meshes.h"
#include "../objects/drawable/singleMeshDrawable/singleMeshDrawable.h"

class LoadingScene : public Scene {
public:
	LoadingScene(Renderer& renderer, std::string name);
	void onLoad() override;
	void update(float deltaTime) override;
	void handleInput(Window& wnd, float delta) override;
};