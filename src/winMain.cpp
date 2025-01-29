#include <string>

#include "graphics/window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window wnd(800, 600, "E-tron");

	MSG msg;
	BOOL gResult;
	while ( (gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) { // !!! gResult > 0 but not GetMessage > 0
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return gResult == -1 ? -1 : msg.wParam;
}