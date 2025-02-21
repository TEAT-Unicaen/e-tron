#include "app.h"

#include <random>

App::App()
	: wnd(800, 800, "E-Tron") {
	
	// Randomly generate X cubes for testing
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disxy(-75.0f, 75.0f);
	std::uniform_real_distribution<float> disz(25.0f, 100.0f);
	std::uniform_real_distribution<float> disrot(-dx::XM_PI, dx::XM_PI);
	for (auto i = 0; i < 50000; i++) {
		float x = disxy(gen);  // Random X position
		float y = disxy(gen); // Random Y position
		float z = disz(gen);  
		float rotx = 2*disrot(gen);
		float roty = 2*disrot(gen);
		float rotz = 2*disrot(gen);
		this->pDrawables.push_back(std::make_unique<Cube>(
			this->wnd.getRenderer(),
			dx::XMFLOAT3{ x, y, z },
			dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
			dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
			dx::XMFLOAT3{ rotx, roty, rotz }
		));
	}

	this->wnd.getRenderer().setProjection(dx::XMMatrixPerspectiveLH(1.0f, 3.0f/4.0f, 0.5f, 100.0f));
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
	renderer.fill(BLACK);
	for (auto& pDrawable : this->pDrawables) {
		pDrawable->update(delta);
		pDrawable->draw(renderer);
	}

	renderer.render();
}