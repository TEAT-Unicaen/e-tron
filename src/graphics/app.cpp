#include "app.h"

#include <random>
#include <io.h>


App::App()
	: wnd(800, 600, "E-Tron") {
	HR;
	// COM initialization
	CHECK_WIN32API_EXCEPT(CoInitialize(nullptr));
	// Randomly generate X cubes for testing

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

	std::array<Color, 9> colorsBasicMotorcycle = {
		Color::RED,
		Color::GREEN,
		Color::BLUE,
		Color::MAGENTA,
		Color::CYAN,
		Color::YELLOW,
		Color::SILVER,
		Color::GRAY,
		Color::WHITE
	};

	std::shared_ptr<Image> pImageCube = std::make_shared<Image>(L"assets/img/cube.png");
	std::shared_ptr<Image> pImageSquarePyramid = std::make_shared<Image>(L"assets/img/squarePyramid.png");

	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disxy(-25.0f, 25.0f);
	std::uniform_real_distribution<float> disz(-50.0f, 50.0f);
	std::uniform_real_distribution<float> disrot(-dx::XM_PI, dx::XM_PI);
	for (auto i = 0; i < 500; i++) {
		float x = disxy(gen);  // Random X position
		float y = disxy(gen); // Random Y position
		float z = disz(gen);
		float rotx = 2 * disrot(gen);
		float roty = 2 * disrot(gen);
		float rotz = 2 * disrot(gen);
		this->pDrawables.push_back(std::make_unique<TexturedSquarePyramid>(
			this->wnd.getRenderer(),
			dx::XMFLOAT3{ x, y, z },
			dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
			dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
			dx::XMFLOAT3{ rotx, roty, rotz },
			pImageSquarePyramid
		));
	}

	/*
	this->pDrawables.push_back(std::make_unique<BasicMotorcycle>(
		this->wnd.getRenderer(),
		dx::XMFLOAT3{ 0.0f, 0.0f, 5.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.5f, 0.5f, 0.0f },
		colorsBasicMotorcycle
	)); 


	this->pDrawables.push_back(std::make_unique<TexturedSquarePyramid>(
		this->wnd.getRenderer(),
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.5f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.5f, 0.0f },
		pImageSquarePyramid

	));
	//GraphicsPlayer player(1, 0.0f, 0.0f, 5.0f, Color::RED, this->wnd.getRenderer());
	//this->pDrawables.push_back(std::make_unique<GraphicsPlayer>(player));
	*/
}

App::~App() {
	CoUninitialize();
}

int App::run() {
	while (true) { // !!! gResult > 0 but not GetMessage > 0
		//Check the window messages and quit 
		if (const auto eCode = wnd.processMessages()) {
			return *eCode;
		}
		this->checkInput();
		this->update();
		SLEEP_MS(1);
	}
}

void App::checkInput() {
	Camera& cam = wnd.getRenderer().getCamera();
	float forward = 0.0f, right = 0.0f;
	float rotX = 0.0f, rotY = 0.0f;
	float speed = 0.1f;
	float rotationSpeed = 0.1f;
	float deltaFOV = 0.0f;

	auto& keyEvent = this->wnd.keyEvent;

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


void App::update() {
	Renderer& ren = wnd.getRenderer();
	auto delta = this->timer.mark();
	if (!this->isPaused) {
		ren.fill(Color::BLACK);
		for (auto& pDrawable : this->pDrawables) {
			pDrawable->update(delta);
			pDrawable->draw(ren);
		}
	} else {
		//TODO : Pause menu
	}

	ren.render();
}