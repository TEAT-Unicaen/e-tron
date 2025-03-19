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

	std::shared_ptr<Image> pImg = std::make_shared<Image>(L"assets/img/squarePyramid.png");
	Mesh pyramid = Pyramid(renderer);
	this->pDrawables.push_back(std::make_unique<SingleMeshDrawable>(
		this->renderer,
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		pyramid,
		L"texturedVS",
		L"texturedPS",
		pImg
	));
	this->pDrawables[0]->setScale(dx::XMFLOAT3(3.0f, 2.5f, 3.0f));
}

void LoadingScene::update(float deltaTime) {
	//this->pDrawables[0]->rotate(dx::XMFLOAT3(0.0f, deltaTime * 200.0f, 0.0f), 0.1f);
	Scene::update(deltaTime);
	this->renderer.renderText(L"Loading...", dx::XMFLOAT2(350, 420), 16, Color::WHITE);
}

void LoadingScene::handleInput(Window& wnd, float delta) {}

