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

	float frameTime = 0.0f;  // Time elapsed since last frame
	UINT frameCount = 0;     // Number of frames since last FPS calculation
	UINT fps = 0;            // FPS count
};