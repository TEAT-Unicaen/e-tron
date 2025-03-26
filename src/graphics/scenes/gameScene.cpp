#include "gameScene.h"


GameScene::GameScene(Renderer& renderer, std::string name)
	: Scene(renderer, name), light(Light(renderer, dx::XMFLOAT3(0.0f, 2.0f, 0.0f), Color::WHITE)), dataLinker(DataLinker()) {}


void GameScene::onLoad() {
	// load the simulation data
	std::string configFilePath = "config.ini";
	if (!std::filesystem::exists(configFilePath)) {
		throw ETRON_EXCEPT("Config file not found");
	}
	ConfigLoader config(configFilePath);
	

	int numPlayers = config.getInt("num_players");
	this->mapSize = config.getInt("grid_size", numPlayers);
	bool rdPos = config.getBool("use_random_pos", true);
	std::string algo = config.getString("algo", "BFS");
	int depths = config.getInt("depths", 3);
	this->timeAutoPlayMax = config.getInt("wait_amount", 100);

	MovingAlgorithmsManager::AlgoEnum algoEnum;

	if (algo == "BFS") {
		algoEnum = MovingAlgorithmsManager::AlgoEnum::BFS;
	}	
	else if (algo == "SOS") {
		algoEnum = MovingAlgorithmsManager::AlgoEnum::SOS;
	}
	else {
		algoEnum = MovingAlgorithmsManager::AlgoEnum::SMART;
	}

	GameManager gameManager(this->mapSize, this->mapSize, numPlayers, rdPos, algoEnum, depths, false, this->timeAutoPlayMax, true, &this->dataLinker);
	gameManager.loop();
	while (!gameManager.isRunning()) { SLEEP_MS(5); }

	// load the graphics
	this->pDrawables.reserve(numPlayers + 2);
	std::shared_ptr<Image> pImg = std::make_shared<Image>(L"assets/img/sky.png");
	pImg->inverse();
	std::unique_ptr<Drawable> skyBox = std::make_unique<SkyBox>(this->renderer, pImg, 5000.0f);
	skyBox->setPosition(dx::XMFLOAT3(0.0f, 350.0f, 0.0f));
	this->pDrawables.push_back(std::move(skyBox));
	float halfSize = this->mapSize / 2;
	std::unique_ptr<Drawable> grid = std::make_unique<Grid3D>(
		this->renderer,
		this->mapSize,
		this->mapSize,
		Drawable::getMesh("plane")
	);
	grid->setPosition(dx::XMFLOAT3(-halfSize, 0.0f, -halfSize));
	this->pDrawables.push_back(std::move(grid));

	
	std::unique_ptr<Drawable> underGrid = std::make_unique<SingleMeshDrawable>(
		this->renderer,
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		Drawable::getMesh("plane"),
		L"phongVS",
		L"coloredPhongSpherePS",
		Color::WHITE
	);
	underGrid->setScale(dx::XMFLOAT3(this->mapSize, 1.0f, this->mapSize));
	underGrid->setRotation(dx::XMFLOAT3(dx::XM_PI, 0.0f, 0.0f));
	this->pDrawables.push_back(std::move(underGrid));

	this->playersColors.reserve(numPlayers);
	for (int i = 0; i < numPlayers; i++) {
		const Color randomColor = Color::getRandomColor();
		this->playersColors.push_back(randomColor);
		std::pair<int, int> pos = this->dataLinker.getInitPos(i);
		std::unique_ptr<Drawable> motocycle = std::make_unique<MotocycleDrawable>(
			this->renderer,
			dx::XMFLOAT3(pos.first-halfSize, 0.2f, pos.second-halfSize),
			dx::XMFLOAT3(0.0f, 0.0f, 0.0f),
			randomColor,
			Color::DARK_GRAY
		);
		this->pDrawables.push_back(std::move(motocycle));
	}

	while (gameManager.isRunning()) { SLEEP_MS(5); }
	gameManager.stop();

	renderer.getCamera().setPosition(0.0f, 1.5f, 0.0f); // need to be here because there one camera for all scene
}

void GameScene::handleInput(Window& wnd, float delta) {
	Renderer& renderer = wnd.getRenderer();
	Camera& cam = renderer.getCamera();
	float forward = 0.0f, right = 0.0f;
	float rotX = 0.0f, rotY = 0.0f;
	float speed = delta * 15;
	float fovSpeed = delta * 100;
	float rotationSpeed = delta * dx::XM_2PI;
	float deltaFOV = 0.0f;

	auto& keyEvent = wnd.keyEvent;

	if (keyEvent.keyIsPressed(VK_ESCAPE) && !this->unspamButton) {
		this->isPaused = !this->isPaused;
		this->unspamButton = true;
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

	if (keyEvent.keyIsPressed('C')) this->light.setColor(renderer, Color::getRandomColor());

	// Camera rotation
	if (keyEvent.keyIsPressed(VK_UP)) rotX -= rotationSpeed; // Rotation vers le bas
	if (keyEvent.keyIsPressed(VK_DOWN)) rotX += rotationSpeed; // Rotation vers le haut
	if (keyEvent.keyIsPressed(VK_LEFT)) rotY -= rotationSpeed; // Rotation à gauche
	if (keyEvent.keyIsPressed(VK_RIGHT)) rotY += rotationSpeed; // Rotation à droite

	// Camera FOV
	if (keyEvent.keyIsPressed('P')) deltaFOV += fovSpeed;
	if (keyEvent.keyIsPressed('M')) deltaFOV -= fovSpeed;

	if (keyEvent.keyIsPressed(VK_SPACE) && !this->unspamButton) {
		this->roundCounter++;
		this->unspamButton = true;
	}

	if (keyEvent.keyIsPressed('A') && !this->unspamButton) {
		this->autoPlay = !this->autoPlay;
		this->unspamButton = true;
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
	if (this->unspamButton) {
		this->time += deltaTime;
		if (this->time > 0.2f) {
			this->time = 0.0f;
			this->unspamButton = false;
		}
	}
	if (this->autoPlay && !this->isPaused) {
		this->timeAutoPlay += deltaTime;
		if (this->timeAutoPlay > this->timeAutoPlayMax / 1000) {
			this->timeAutoPlay = 0.0f;
			this->roundCounter++;
		}
	}
	if (this->roundCounter < this->dataLinker.getData().size()) {
		auto& data = this->dataLinker.getData().at(this->roundCounter);
		float halfSize = this->mapSize / 2;
		this->pDrawables[data.id + 2]->moveInTo(dx::XMFLOAT3(data.newX-halfSize, 0.2f, data.newY-halfSize), 0.1f);
		UINT slot = data.x * this->mapSize + data.y;
		static_cast<Grid3D*>(this->pDrawables[1].get())->getInstanceBuffer().updateInstance(renderer, slot, this->playersColors[data.id-1]);
	}

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