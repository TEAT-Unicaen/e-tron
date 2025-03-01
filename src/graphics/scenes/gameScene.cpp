#include "gameScene.h"

GameScene::GameScene(Renderer& renderer, std::string name) : Scene(renderer, name) {}

void GameScene::onLoad() {
	OutputDebugStringA("GameScene loading\n");
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

	OutputDebugStringA("Images loading\n");
	//std::shared_ptr<Image> pImageCube = std::make_shared<Image>(L"assets/img/cube.png");
	//std::shared_ptr<Image> pImageSquarePyramid = std::make_shared<Image>(L"assets/img/squarePyramid.png");
	OutputDebugStringA("Images loaded\n");

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-50.0f, 50.0f);
	std::uniform_real_distribution<float> rot(-2 * dx::XM_PI, 2 * dx::XM_PI);
	std::uniform_real_distribution<float> move(-5.0f, 5.0f);
	for (auto i = 0; i < 500; i++) {
		float x = dis(gen);
		float y = dis(gen);
		float z = dis(gen);
		float rotx = rot(gen);
		float roty = rot(gen);
		float rotz = rot(gen);
		float movex = move(gen);
		float movey = move(gen);
		float movez = move(gen);

		this->pDrawables.push_back(std::make_unique<ColoredTore>(
			this->renderer,
			dx::XMFLOAT3{ x, y, z },
			dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
			dx::XMFLOAT3{ movex, movey, movez },
			dx::XMFLOAT3{ rotx, roty, rotz },
			colorsSphere
		));
	}
	OutputDebugStringA("GameScene loaded\n");
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