#include "loadingScene.h"

LoadingScene::LoadingScene(Renderer& renderer, std::string name) : Scene(renderer, name) {}

void LoadingScene::onLoad() {
	std::vector<Color> colorsCube = {
	Color::RED,
	Color::GREEN,
	Color::BLUE,
	Color::MAGENTA,
	Color::CYAN,
	Color::YELLOW
	};

	std::shared_ptr<Image> pImg = std::make_shared<Image>(L"assets/img/obamium.png");
	Mesh cube = Cube(renderer);
	this->pDrawables.push_back(std::make_unique<SingleMeshDrawable>(
		this->renderer,
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		cube,
		L"defaultVS",
		L"coloredCubePS",
		colorsCube
	));
}

void LoadingScene::update(float deltaTime) {
	Scene::update(deltaTime);
	this->renderer.renderText(L"Loading...", dx::XMFLOAT2(350, 420), 16, Color::WHITE);
}

void LoadingScene::handleInput(Window& wnd, float delta) {}

