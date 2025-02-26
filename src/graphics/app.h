#pragma once

#include <thread>

#include "window.h"
#include "appTimer.h"
#include "../utils/utils.h"
#include "objects/objects.h"

#include "gameObjects/BasicMotorcycle.h"

class App {
public :
	App();
	~App();
	int run();
private:
	void checkInput();
	void update();
	
	Window wnd;
	AppTimer timer;
	std::vector<std::unique_ptr<Drawable>> pDrawables;

	bool isPaused = false;
};