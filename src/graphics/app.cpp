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


	Renderer::Vertex v1 = { {0.5f, -0.5f, 0.25f}, {RED, 255} };
	Renderer::Vertex v2 = { {0.0f, 0.5f, 0.25f}, {BLUE, 255} };
	Renderer::Vertex v3 = { {-0.5f, -0.5f, 0.25f}, {GREEN, 255} };
	renderer.addTriangle(v1, v3, v2);

	Renderer::Vertex v4 = { {-0.75f, -0.75f, 0.0f}, {BLACK, 255} };
	Renderer::Vertex v5 = { {0.75f, 0.75f, 0.0}, {BLACK, 255} };
	renderer.addLine(v4, v5);// it is under the triangle

	renderer.drawAll();

	renderer.render();
}