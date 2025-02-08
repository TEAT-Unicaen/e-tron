#include "app.h"

App::App()
	: wnd(800, 800, "E-Tron") {}

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
	renderer.fill(WHITE);

	Renderer::Vertex v1 = { {0.5f, -0.5f}, {RED, 255} };
	Renderer::Vertex v2 = { {0.0f, 0.5f}, {GREEN, 255} };
	Renderer::Vertex v3 = { {-0.5f, -0.5f}, {BLUE, 255} };
	renderer.addTriangle(v1, v3, v2);

	renderer.DrawAll();

	renderer.render();
}