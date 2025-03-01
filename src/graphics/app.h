#pragma once

#include <thread>

#include "core/window.h"
#include "utils/appTimer.h"
#include "../utils/utils.h"

#include "scenes/scenes.h"

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
	
	std::unique_ptr<SceneManager> sceneManager;

	float frameTime = 0.0f;  // Time elapsed since last frame
	UINT frameCount = 0;     // Number of frames since last FPS calculation
	UINT fps = 0;            // FPS count
};