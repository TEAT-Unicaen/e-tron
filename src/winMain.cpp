#include <string>
#include <Windows.h>
#include "graphics/window.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nCmdShow) {
	try {
		Window wnd(800, 600, "E-tron");

		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) { // !!! gResult > 0 but not GetMessage > 0
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return gResult == -1 ? -1 : msg.wParam;
	}
	catch (const TronException& e) {
		MessageBox(nullptr, e.what(), e.getType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e) {
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...) {
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -999;
}