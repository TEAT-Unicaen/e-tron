#pragma once

#include <thread>

#include "window.h"
#include "appTimer.h"
#include "../utils/utils.h"

class App {
public :
	App();
	~App() = default;
	int run();
private:
	void update();
	
	Window wnd;
	AppTimer timer;
};