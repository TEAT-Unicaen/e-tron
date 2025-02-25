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
	std::uniform_real_distribution<float> disxy(-50.0f, 50.0f);
	std::uniform_real_distribution<float> disz(-50.0f, 50.0f);
	std::uniform_real_distribution<float> disrot(-dx::XM_PI, dx::XM_PI);
	for (auto i = 0; i < 1000; i++) {
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

<<<<<<< HEAD
	
	this->pDrawables.push_back(std::make_unique<BasicMotorcycle>(
		this->wnd.getRenderer(),
		dx::XMFLOAT3{ 0.0f, 0.0f, 5.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.5f, 0.5f, 0.0f },
		colorsBasicMotorcycle
	)); 

=======
>>>>>>> e31d5c5 (make a utils folder in graphics | add camera(movable))
	/*
	this->pDrawables.push_back(std::make_unique<TexturedSquarePyramid>(
		this->wnd.getRenderer(),
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.5f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.5f, 0.0f },
		pImageSquarePyramid
<<<<<<< HEAD
	)); */
=======
	));*/
>>>>>>> e31d5c5 (make a utils folder in graphics | add camera(movable))

	//GraphicsPlayer player(1, 0.0f, 0.0f, 5.0f, Color::RED, this->wnd.getRenderer());
	//this->pDrawables.push_back(std::make_unique<GraphicsPlayer>(player));
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

		this->update();
	}
}

void App::update() {
	Renderer& ren = wnd.getRenderer();
	Camera& cam = ren.getCamera();
	if (this->wnd.keyEvent.keyIsPressed('Z')) {
		cam.move(0.1f, 0.0f, 0.0f); // Avancer dans la direction du regard
	}
	if (this->wnd.keyEvent.keyIsPressed('S')) {
		cam.move(-0.1f, 0.0f, 0.0f); // Reculer
	}
	if (this->wnd.keyEvent.keyIsPressed('Q')) {
		cam.move(0.0f, -0.1f, 0.0f); // Strafe gauche
	}
	if (this->wnd.keyEvent.keyIsPressed('D')) {
		cam.move(0.0f, 0.1f, 0.0f); // Strafe droite
	}
	if (this->wnd.keyEvent.keyIsPressed('P')) {
		cam.updateFOV(0.5);
	}
	if (this->wnd.keyEvent.keyIsPressed('M')) {
		cam.updateFOV(-0.5);
	}
	
	// Rotation
	if (this->wnd.keyEvent.keyIsPressed(VK_UP)) {
		cam.rotate(-0.1f, 0.0f, 0.0f);
	}
	if (this->wnd.keyEvent.keyIsPressed(VK_DOWN)) {
		cam.rotate(0.1f, 0.0f, 0.0f);
	}
	if (this->wnd.keyEvent.keyIsPressed(VK_LEFT)) {
		cam.rotate(0.0f, -0.1f, 0.0f);
	}
	if (this->wnd.keyEvent.keyIsPressed(VK_RIGHT)) {
		cam.rotate(0.0f, 0.1f, 0.0f);
	}
	if (this->wnd.keyEvent.keyIsPressed('R')) {
		cam.setPosition(0.0f, 0.0f, -5.0f);
		cam.setRotation(0.0f, 0.0f, 0.0f);
		cam.setFOV(90.0f);
	}


	auto delta = this->timer.mark();
	ren.fill(Color::BLACK);
	for (auto& pDrawable : this->pDrawables) {
		pDrawable->update(delta);
		pDrawable->draw(ren);
	}

	ren.render();
}