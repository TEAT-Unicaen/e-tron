 #include "gameScene.h"

GameScene::GameScene(Renderer& renderer, std::string name)
	: Scene(renderer, name), light(Light(renderer, dx::XMFLOAT3(0.0f, 5.0f, 0.0f), Color::WHITE)) {}

void GameScene::onLoad() {
	std::vector<Color> colorsCube = {
		Color::RED,
		Color::GREEN,
		Color::BLUE,
		Color::MAGENTA,
		Color::CYAN,
		Color::YELLOW
	};

	std::vector<Color> colorsSquarePyramid = {
		Color::RED,
		Color::GREEN,
		Color::BLUE,
		Color::MAGENTA,
		Color::CYAN,
	};

	std::vector<Color> colorsCylinder = {
		Color::CYAN,
		Color::SILVER,
		Color::GRAY,
	};

	std::shared_ptr<Image> pImageCube = std::make_shared<Image>(L"assets/img/cube.png");
	std::shared_ptr<Image> pImageSquarePyramid = std::make_shared<Image>(L"assets/img/squarePyramid.png");

	Mesh cube = Cube(renderer);
	Mesh squarePyramid = Pyramid(renderer);
	Mesh cylinder = Cylinder(renderer);
	Mesh sphere = Sphere(renderer);
	Mesh tore = Tore(renderer);
	Mesh cone = Cone(renderer);
	Mesh plane = Plane(renderer);

	std::unique_ptr<Drawable> pSquarePyramid = std::make_unique<SingleMeshDrawable>(
		this->renderer,
		dx::XMFLOAT3{ 1.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		squarePyramid,
		L"phongVS",
		L"coloredPhongSpherePS",
		Color::GREEN
	);

	std::unique_ptr<Drawable> pCylinder = std::make_unique<SingleMeshDrawable>(
		this->renderer,
		dx::XMFLOAT3{ 0.0f, 0.0f, -5.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		cylinder,
		L"phongVS",
		L"coloredPhongSpherePS",
		Color::BLUE
	);
	
	std::unique_ptr<Drawable> pSphere = std::make_unique<SingleMeshDrawable>(
		this->renderer,
		dx::XMFLOAT3{ 0.0f, -5.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		sphere,
		L"phongVS",
		L"coloredPhongSpherePS",
		Color::CYAN
	);

	std::unique_ptr<Drawable> pTore = std::make_unique<SingleMeshDrawable>(
		this->renderer,
		dx::XMFLOAT3{ 0.0f, 2.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		tore,
		L"phongVS",
		L"coloredPhongSpherePS",
		Color::MAGENTA
	);

	std::unique_ptr<Drawable> pCone = std::make_unique<SingleMeshDrawable>(
		this->renderer,
		dx::XMFLOAT3{ -2.0f, 2.5f, 2.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		cone,
		L"phongVS",
		L"coloredPhongSpherePS",
		Color::YELLOW
	);

	std::unique_ptr<Drawable> pPlane = std::make_unique<SingleMeshDrawable>(
		this->renderer,
		dx::XMFLOAT3{ 0.0f, -5.0f, 0.0f },
		dx::XMFLOAT3{ dx::XM_PIDIV2, 0.0f, 0.0f },
		plane,
		L"phongVS",
		L"coloredPhongSpherePS",
		Color::WHITE
	);

	pTore->setScale(dx::XMFLOAT3(2.0f, 2.0f, 2.0f));
	pPlane->setScale(dx::XMFLOAT3(10.0f, 10.0f, 10.0f));

	UINT size = 100;
	std::unique_ptr<Drawable> grid = std::make_unique<Grid3D>(
		this->renderer,
		size,
		size,
		cube
	);

	this->pDrawables.push_back(std::move(grid));
	

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
	if (keyEvent.keyIsPressed('I')) {
		this->light.position.y += 0.1f;
	}
	if (keyEvent.keyIsPressed('K')) {
		this->light.position.y -= 0.1f;
	}
	if (keyEvent.keyIsPressed('J')) {
		this->light.position.x -= 0.1f;
	}
	if (keyEvent.keyIsPressed('L')) {
		this->light.position.x += 0.1f;
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