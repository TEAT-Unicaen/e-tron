#include <string>
#include <Windows.h>
#include "graphics/window.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nCmdShow) {
	try {
		Window wnd(800, 600, "E-tron");

		MSG msg;
		BOOL gResult;
		std::string title = "E-tron";
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) { // !!! gResult > 0 but not GetMessage > 0
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			while (!wnd.mouseEvent.isEmpty() ) {
				const auto e = wnd.mouseEvent.read();
				if (!e.has_value())
					continue;
				switch (e.value().getType()) {
					case MouseEventManager::Event::Type::Leave:
						title = "Mouse Leave";
						break;
					case MouseEventManager::Event::Type::Move:
						title = "Mouse Move (" + std::to_string(e.value().getCoords().x) + ", " + std::to_string(e.value().getCoords().y) + ")";
						break;
					case MouseEventManager::Event::Type::Press:
						switch (e.value().getButton()) {
						case MouseEventManager::Button::Left:
							title = "Mouse Pressed: Left";
							break;
						case MouseEventManager::Button::Right:
							title = "Mouse Pressed: Right";
							break;
						case MouseEventManager::Button::Middle:
							title = "Mouse Pressed: Middle";
							break;
						case MouseEventManager::Button::Button4:
							title = "Mouse Pressed: Button4";
							break;
						case MouseEventManager::Button::Button5:
							title = "Mouse Pressed: Button5";
							break;
						}
						break;
					case MouseEventManager::Event::Type::WheelUp:
						title = "Mouse Wheel Up";
						break;
					case MouseEventManager::Event::Type::WheelDown:
						title = "Mouse Wheel Down";
						break;
				}
				wnd.setTitle(title);
			}
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