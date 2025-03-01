#include "loadingScene.h"

LoadingScene::LoadingScene(Renderer& renderer, std::string name) : Scene(renderer, name) {}

void LoadingScene::onLoad() {
	std::shared_ptr<Image> pImg = std::make_shared<Image>(L"assets/img/obamium.png");

	this->pDrawables.push_back(std::make_unique<TexturedSquarePyramid>(
		this->renderer,
		dx::XMFLOAT3(0.0f, 0.0f, -2.0f),
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		dx::XMFLOAT3(0.0f, 5.0f, 0.0f),
		pImg
	));
}

void LoadingScene::update(float deltaTime) {
	Scene::update(deltaTime);
	this->renderer.renderText(L"Loading...", dx::XMFLOAT2(350, 400), 16, Color::WHITE);
}

void LoadingScene::handleInput(Window& wnd) {}

