 #include "gameScene.h"

GameScene::GameScene(Renderer& renderer, std::string name)
	: Scene(renderer, name), light(Light(renderer, dx::XMFLOAT3(0.0f, 5.0f, 0.0f), Color::WHITE)), dataLinker(DataLinker()) {}


void GameScene::onLoad() {
	// load the simulation data
	OutputDebugString("Loading simulation data...\n");
	std::string configFilePath = "config.ini";
	if (!std::filesystem::exists(configFilePath)) {
		throw ETRON_EXCEPT("Config file not found");
	}
	ConfigLoader config(configFilePath);
	

	int numPlayers = config.getInt("num_players");
	int size = config.getInt("grid_size", numPlayers);
	bool rdPos = config.getBool("use_random_pos", true);
	bool useSos = config.getBool("movement_use_SOS", false);
	bool showEachStep = config.getBool("show_each_step", true);
	int waitAmount = config.getInt("wait_amount", 100);
	OutputDebugString("Simulation config loaded\n");

	GameManager gameManager(size, size, numPlayers, rdPos, useSos, showEachStep, waitAmount, true, &this->dataLinker);
	gameManager.loop();

	OutputDebugStringA("Game loop started\n");

	// load the graphics
	std::shared_ptr<Image> pImg = std::make_shared<Image>(L"assets/img/sky.png");
	pImg->inverse();
	std::unique_ptr<Drawable> skyBox = std::make_unique<SkyBox>(this->renderer, pImg, 5000.0f);
	skyBox->setPosition(dx::XMFLOAT3(0.0f, 350.0f, 0.0f));
	this->pDrawables.push_back(std::move(skyBox));

	std::unique_ptr<Drawable> grid = std::make_unique<Grid3D>(
		this->renderer,
		size,
		size,
		Drawable::getMesh("plane")
	);
	this->pDrawables.push_back(std::move(grid));

	std::unique_ptr<Drawable> motocycle = std::make_unique<MotocycleDrawable>(
		this->renderer,
		dx::XMFLOAT3(0.0f, 0.1f, 0.0f),
		dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
		Color::GREEN
	);
	this->pDrawables.push_back(std::move(motocycle));
	
	renderer.getCamera().setPosition(0.0f, 1.5f, 0.0f);

	// wait the data
	OutputDebugString("Waiting for the simulation to start...\n");
	while (gameManager.isRunning()) { SLEEP(5); }
	gameManager.stop();
	OutputDebugString("Simulation started\n");
}

void GameScene::handleInput(Window& wnd, float delta) {
	Renderer& renderer = wnd.getRenderer();
	Camera& cam = renderer.getCamera();
	float forward = 0.0f, right = 0.0f;
	float rotX = 0.0f, rotY = 0.0f;
	float speed = delta * 15;
	float rotationSpeed = delta * dx::XM_2PI;
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
		this->pDrawables[2]->moveInTo(dx::XMFLOAT3(0.0f, 0.1f, 1.0f), 0.1f);
		static_cast<Grid3D*>(this->pDrawables[1].get())->getInstanceBuffer().updateInstance(renderer, 5050u, Color::GREEN);
	}
	if (keyEvent.keyIsPressed('G')) {
		this->pDrawables[2]->moveInTo(dx::XMFLOAT3(0.0f, 0.1f, 2.0f), 0.1f);
		static_cast<Grid3D*>(this->pDrawables[1].get())->getInstanceBuffer().updateInstance(renderer, 5051u, Color::GREEN);
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

	if (keyEvent.keyIsPressed('O')) {
		for (auto& data : this->dataLinker.data) {
			std::string keyStr = "Key : " + std::to_string(data.first) + "\n";
			OutputDebugString(keyStr.c_str());
			for (auto& dataS : data.second) {
				std::string valStr = "Data : " + std::to_string(dataS) + "\n";
				OutputDebugString(valStr.c_str());
			}
			OutputDebugStringA("\n");
		}
		SLEEP_MS(100);
	}

	if (keyEvent.keyIsPressed(VK_SPACE)) {
		this->roundCounter++;
		SLEEP_MS(100);
	}

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

	auto& data = this->dataLinker.data.at(this->roundCounter);
	this->pDrawables[data.first+1]->moveInTo(dx::XMFLOAT3(data.second[2], 0.1f, data.second[3]), 0.1f);


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