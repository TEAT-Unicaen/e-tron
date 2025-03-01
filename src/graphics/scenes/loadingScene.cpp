#include "loadingScene.h"

LoadingScene::LoadingScene(Renderer& renderer, std::string name) : Scene(renderer, name) {}

void LoadingScene::onLoad() {
	std::shared_ptr<Image> pImg = std::make_shared<Image>(L"assets/img/obamium.png");

	std::unique_ptr obj = std::move(std::make_unique<Object>()) ;
	obj->add(std::make_unique<TexturedSquarePyramid>(
		this->renderer,
		dx::XMFLOAT3(0.0f, 0.0f, -3.0f),
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		dx::XMFLOAT3(0.0f, 5.0f, 0.0f),
		pImg
	));
	this->pDrawables.push_back(std::move(obj));
}

void LoadingScene::update(float deltaTime) {
	Scene::update(deltaTime);
	this->renderer.renderText(L"Loading...", dx::XMFLOAT2(350, 420), 16, Color::WHITE);
}

void LoadingScene::handleInput(Window& wnd) {}

