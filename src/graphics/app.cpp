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
	renderer.fill(255.0f, 255.0f, 255.0f);

	renderer.render();
}