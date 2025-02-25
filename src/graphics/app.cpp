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

	std::shared_ptr<Image> pImageCube = std::make_shared<Image>(L"assets/img/cube.png");
	std::shared_ptr<Image> pImageSquarePyramid = std::make_shared<Image>(L"assets/img/squarePyramid.png");

	/*
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disxy(-5.0f, 5.0f);
	std::uniform_real_distribution<float> disz(5.0f, 20.0f);
	std::uniform_real_distribution<float> disrot(-dx::XM_PI, dx::XM_PI);
	for (auto i = 0; i < 20; i++) {
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
	}*/

	this->pDrawables.push_back(std::make_unique<TexturedSquarePyramid>(
		this->wnd.getRenderer(),
		dx::XMFLOAT3{ 0.0f, 0.0f, 5.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.5f, 0.0f },
		pImageSquarePyramid
	));

	//GraphicsPlayer player(1, 0.0f, 0.0f, 5.0f, Color::RED, this->wnd.getRenderer());
	//this->pDrawables.push_back(std::make_unique<GraphicsPlayer>(player));
	


	this->wnd.getRenderer().setProjection(dx::XMMatrixPerspectiveLH(
		1.0f, // with ratio
		(float)this->wnd.getHeight() / this->wnd.getWidth(), // height ratio
		0.5f, // near plane
		1000.0f // far plane
	));
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
	Renderer& renderer = wnd.getRenderer();

	auto delta = this->timer.mark();
	renderer.fill(Color::BLACK);
	for (auto& pDrawable : this->pDrawables) {
		pDrawable->update(delta);
		pDrawable->draw(renderer);
	}

	renderer.render();
}