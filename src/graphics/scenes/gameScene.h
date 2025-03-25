#pragma once

#include "scene.h"
#include "../objects/meshes/meshes.h"
#include "../objects/drawable/singleMeshDrawable/singleMeshDrawable.h"
#include "../objects/drawable/instancedMeshDrawable/instancedMeshDrawable.h"
#include "../objects/light.h"
#include <memory>
#include <filesystem>

#include "../objects/drawable/skyBox.h"
#include "../objects/drawable/instancedMeshDrawable/grid3D/grid3D.h"
#include "../objects/drawable/compositeDrawable/motocycle/motocycleDrawable.h"

// simulation logic
#include "../../utils/configLoader.h"
#include "../../manager/gameManager.h"


class GameScene : public Scene {
public:
	GameScene(Renderer& renderer, std::string name);

	void onLoad() override;

	void update(float deltaTime) override;
	void handleInput(Window& wnd, float delta) override;

private:
	bool isPaused = false;
	Light light;

	DataLinker dataLinker;

	UINT roundCounter = 0;
	UINT mapSize = 1;

	float time = 0.0f;
	bool unspamButton = false;

	bool autoPlay = false;
};