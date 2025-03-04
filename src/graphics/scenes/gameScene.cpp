#include "gameScene.h"

GameScene::GameScene(Renderer& renderer, std::string name) : Scene(renderer, name) {}

void GameScene::onLoad() {
	std::array<Color, 6> colorsCube = {
		Color::RED,
		Color::GREEN,
		Color::BLUE,
		Color::MAGENTA,
		Color::CYAN,
		Color::YELLOW
	};

	std::array<Color, 5> colorsSquarePyramid = {
		Color::RED,
		Color::GREEN,
		Color::BLUE,
		Color::MAGENTA,
		Color::CYAN,
	};

	std::array<Color, 3> colorsCylinder = {
		Color::CYAN,
		Color::SILVER,
		Color::GRAY,
	};

	std::array<Color, 1> colorsSphere = {
		Color::SILVER
	};
	//std::shared_ptr<Image> pImageCube = std::make_shared<Image>(L"assets/img/cube.png");
	//std::shared_ptr<Image> pImageSquarePyramid = std::make_shared<Image>(L"assets/img/squarePyramid.png");

	this->pDrawables.push_back(std::make_unique<CubeGrid>(
		this->renderer,
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		colorsCube,
		10, 10
	));
	this->pDrawables.push_back(std::make_unique<MotorPlayer>(
		this->renderer,
		dx::XMFLOAT3{ 2.0f, 4.0f, 2.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		colorsCylinder
	));
}

void GameScene::handleInput(Window& wnd) {
	Camera& cam = wnd.getRenderer().getCamera();
	float forward = 0.0f, right = 0.0f;
	float rotX = 0.0f, rotY = 0.0f;
	float speed = 0.1f;
	float rotationSpeed = 0.1f;
	float deltaFOV = 0.0f;

	auto& keyEvent = wnd.keyEvent;

	if (keyEvent.keyIsPressed(VK_ESCAPE)) {
		this->isPaused = !this->isPaused;
		SLEEP_MS(100);
	}

	if (this->isPaused) return;

	// Camera movement
	if (keyEvent.keyIsPressed('Z')) forward += 1.0f;
	if (keyEvent.keyIsPressed('S')) forward -= 1.0f;
	if (keyEvent.keyIsPressed('Q')) right -= 1.0f;
	if (keyEvent.keyIsPressed('D')) right += 1.0f;

	// Normalized movement
	if (keyEvent.keyIsPressed(VK_SHIFT)) speed *= 5;
	float length = std::sqrt(forward * forward + right * right);
	if (length > 0.0f) {
		forward = (forward / length) * speed;
		right = (right / length) * speed;
	}

	// Camera rotation
	if (keyEvent.keyIsPressed(VK_UP)) rotX -= rotationSpeed; // Rotation vers le bas
	if (keyEvent.keyIsPressed(VK_DOWN)) rotX += rotationSpeed; // Rotation vers le haut
	if (keyEvent.keyIsPressed(VK_LEFT)) rotY -= rotationSpeed; // Rotation à gauche
	if (keyEvent.keyIsPressed(VK_RIGHT)) rotY += rotationSpeed; // Rotation à droite

	// Camera FOV
	if (keyEvent.keyIsPressed('P')) deltaFOV += 1.0f;
	if (keyEvent.keyIsPressed('M')) deltaFOV -= 1.0f;

	cam.move(forward, right, 0.0f);
	cam.rotate(rotX, rotY, 0.0f);
	cam.updateFOV(deltaFOV);

	// Reset camera
	if (keyEvent.keyIsPressed('R')) {
		cam.setPosition(0.0f, 0.0f, -5.0f);
		cam.setRotation(0.0f, 0.0f, 0.0f);
		cam.setFOV(90.0f);
	}
}

void GameScene::update(float deltaTime) {
	if (!this->isPaused) {
		Scene::update(deltaTime);
	} else {
		for (auto& pDrawable : this->pDrawables) {
			pDrawable->draw(renderer);
		}
		renderer.renderText(L"PAUSED", dx::XMFLOAT2(700, 10), 16, Color::WHITE);
	}
}