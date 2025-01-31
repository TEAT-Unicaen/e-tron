#include "app.h"

App::App()
	: wnd(800, 800, "E-Tron") {}

int App::run() {
	MSG msg;
	BOOL gResult;
	std::string title = "E-tron";
	while (true) { // !!! gResult > 0 but not GetMessage > 0
		
		//Check the window messages and quit 
		if (const auto eCode = wnd.processMessages()) {
			return *eCode;
		}

		this->update();
	}

	return gResult == -1 ? -1 : msg.wParam;
}


void App::update() {

}