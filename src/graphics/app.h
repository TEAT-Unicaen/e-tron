#pragma once

#include <thread>

#include "window.h"
#include "appTimer.h"
#include "../utils/utils.h"
#include "objects/drawable.h"
#include "objects/cube.h"

class App {
public :
	App();
	~App() = default;
	int run();
private:
	void update();
	
	Window wnd;
	AppTimer timer;
	std::vector<std::unique_ptr<Drawable>> pDrawables;
};