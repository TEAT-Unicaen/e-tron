 #include "gameScene.h"

GameScene::GameScene(Renderer& renderer, std::string name)
	: Scene(renderer, name), light(Light(renderer, dx::XMFLOAT3(0.0f, 5.0f, 0.0f), Color::WHITE)) {}

void GameScene::onLoad() {

	Mesh cube = Cube(renderer);
	Mesh squarePyramid = Pyramid(renderer);
	Mesh cylinder = Cylinder(renderer);
	Mesh sphere = Sphere(renderer);
	Mesh tore = Tore(renderer);
	Mesh cone = Cone(renderer);
	Mesh plane = Plane(renderer);

	UINT size = 100;
	std::unique_ptr<Drawable> grid = std::make_unique<Grid3D>(
		this->renderer,
		size,
		size,
		cube
	);
	this->pDrawables.push_back(std::move(grid));

	std::unique_ptr<Drawable> motocycle = std::make_unique<MotocycleDrawable>(
		this->renderer,
		dx::XMFLOAT3(0.0f, 1.0f, 5.0f),
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		Color::WHITE
	);
	this->pDrawables.push_back(std::move(motocycle));

	std::unique_ptr<Drawable> motocycle1 = std::make_unique<MotocycleDrawable>(
		this->renderer,
		dx::XMFLOAT3(0.0f, 1.0f, -5.0f),
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		Color::RED
	);
	this->pDrawables.push_back(std::move(motocycle1));
	
	
	renderer.getCamera().setPosition(0.0f, 1.5f, 0.0f);
}

void GameScene::handleInput(Window& wnd, float delta) {
	Camera& cam = wnd.getRenderer().getCamera();
	float forward = 0.0f, right = 0.0f;
	float rotX = 0.0f, rotY = 0.0f;
	float speed = delta * 15;
	float rotationSpeed = delta * 7.5f;
	float deltaFOV = 0.0f;

	auto& keyEvent = wnd.keyEvent;

	if (keyEvent.keyIsPressed(VK_ESCAPE)) {
		this->isPaused = !this->isPaused;
		SLEEP_MS(100);
	}

	if (keyEvent.keyIsPressed('V')) {
		wnd.getRenderer().setVSync(true);
	}
	if (keyEvent.keyIsPressed('B')) {
		wnd.getRenderer().setVSync(false);
	}

	if (this->isPaused) return;

	// Camera movement
	if (keyEvent.keyIsPressed('Z')) forward += 0.5f;
	if (keyEvent.keyIsPressed('S')) forward -= 0.5f;
	if (keyEvent.keyIsPressed('Q')) right -= 0.5f;
	if (keyEvent.keyIsPressed('D')) right += 0.5f;

	// Normalized movement
	if (keyEvent.keyIsPressed(VK_SHIFT)) speed *= 5;
	float length = std::sqrtf(forward * forward + right * right);
	if (length > 0.0f) {
		forward = (forward / length) * speed;
		right = (right / length) * speed;
	}

	// Object movement
	if (keyEvent.keyIsPressed('T')) {
		this->pDrawables[0]->move(dx::XMFLOAT3(5.0f, 0.0f, 0.0f), 0.1f);
		this->pDrawables[0]->rotate(dx::XMFLOAT3(0.0f, 0.0f, 0.1f), 0.1f);
	}
	if (keyEvent.keyIsPressed('G')) {
		this->pDrawables[0]->move(dx::XMFLOAT3(-5.0f, 0.0f, 0.0f), 0.1f);
		this->pDrawables[0]->rotate(dx::XMFLOAT3(0.0f, 0.0f, -0.1f), 0.1f);
	}

	// Light movement
	float lightSpeed = 10 * delta;
	if (keyEvent.keyIsPressed('I')) {
		this->light.position.y += lightSpeed;
	}
	if (keyEvent.keyIsPressed('K')) {
		this->light.position.y -= lightSpeed;
	}
	if (keyEvent.keyIsPressed('J')) {
		this->light.position.x -= lightSpeed;
	}
	if (keyEvent.keyIsPressed('L')) {
		this->light.position.x += lightSpeed;
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
		cam.setPosition(0.0f, 1.5f, -5.0f);
		cam.setRotation(0.0f, 0.0f, 0.0f);
		cam.setFOV(90.0f);
	}
}

void GameScene::update(float deltaTime) {
	this->light.bind(renderer);
	if (!this->isPaused) {
		Scene::update(deltaTime);
		this->light.draw(renderer);
	} else {
		for (auto& pDrawable : this->pDrawables) {
			pDrawable->draw(renderer);
		}
		this->light.draw(renderer);
		renderer.renderText(L"PAUSED", dx::XMFLOAT2(700, 10), 16, Color::WHITE);
	}
	
}