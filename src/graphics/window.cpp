#include "window.h"


// Window Class Stuff
Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept 
	: hInst(GetModuleHandle(nullptr)) {
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = Window::handleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = Window::WindowClass::getInstance();
	wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = Window::WindowClass::getName();
	wc.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass() {
	UnregisterClass(Window::WindowClass::wndClassName, Window::WindowClass::getInstance());
}

const char* Window::WindowClass::getName() noexcept {
	return Window::WindowClass::wndClassName;
}

HINSTANCE Window::WindowClass::getInstance() noexcept {
	return Window::WindowClass::wndClass.hInst;
}

// Window Stuff
Window::Window(int width, int height, const char* name, bool handleCloseButton)
	: width(width), height(height), handleCloseButton(handleCloseButton) {
	RECT wr = {0};
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0) {
		throw WIN_EXCEPT(GetLastError());
	}

	this->hWnd = CreateWindowEx(
		0, Window::WindowClass::getName(),
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, Window::WindowClass::getInstance(), this
	);
	if (this->hWnd == nullptr) {
		throw WIN_EXCEPT(GetLastError());
	}
	ShowWindow(this->hWnd, SW_SHOWDEFAULT);
}

Window::~Window() {
	DestroyWindow(this->hWnd);
}

void Window::setTitle(const std::string& title) {
	if (SetWindowText(this->hWnd, title.c_str()) == 0) {
		throw WIN_EXCEPT(GetLastError());
	}
}

LRESULT CALLBACK Window::handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
	if (msg == WM_NCCREATE) {
		// Extract the pointer to the window class
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// Store the pointer inside the USERDATA
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// Change the proc because the setup is done
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::handleMsgThunk));
		return pWnd->handleMsg(hWnd, msg, wParam, lParam);
	}
	// default message
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::handleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
	// Get th pointer to the window class
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	
	return pWnd->handleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
	const POINTS pt = MAKEPOINTS(lParam);
	switch (msg) {
	case WM_CLOSE:
		if (this->handleCloseButton) {
			PostQuitMessage(0);
			return 0;// we don't want to use the default handler message here
		}
		break;
	case WM_KILLFOCUS:
		keyEvent.clearState();
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		// Check if the key is autorepeated. If it was the prevoius input bit 30 true
		if (!(lParam & BIT(30)) || keyEvent.autorepeatIsEnabled()) {
			keyEvent.onKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		keyEvent.onKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		keyEvent.onChar(static_cast<unsigned char>(wParam));
		break;
	case WM_MOUSEMOVE:
		if (pt.x >= 0 && pt.x < this->width && pt.y >= 0 && pt.y < this->height) {
			mouseEvent.onMouseMove(pt.x, pt.y);
			if (!mouseEvent.isInWindow()) {
				SetCapture(hWnd);
				mouseEvent.onMouseEnter(pt.x, pt.y);
			}
		} else {
			if (wParam & (MK_LBUTTON | MK_RBUTTON )) {// check if we drag the mouse out of the window
				mouseEvent.onMouseMove(pt.x, pt.y);
			} else {
				ReleaseCapture();
				mouseEvent.onMouseLeave(pt.x, pt.y);
			}
		}
		
		break;
	case WM_LBUTTONDOWN:
		mouseEvent.onButtonPressed(MouseEventManager::Button::Left, pt.x, pt.y);
		break;
	case WM_RBUTTONDOWN:
		mouseEvent.onButtonPressed(MouseEventManager::Button::Right, pt.x, pt.y);
		break;
	case WM_MBUTTONDOWN:
		mouseEvent.onButtonPressed(MouseEventManager::Button::Middle, pt.x, pt.y);
		break;
	case WM_XBUTTONDOWN:
		if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) {
			mouseEvent.onButtonPressed(MouseEventManager::Button::Button4, pt.x, pt.y);
		}
		else {
			mouseEvent.onButtonPressed(MouseEventManager::Button::Button5, pt.x, pt.y);
		}
		break;
	case WM_LBUTTONUP:
		mouseEvent.onButtonReleased(MouseEventManager::Button::Left, pt.x, pt.y);
		break;
	case WM_RBUTTONUP:
		mouseEvent.onButtonReleased(MouseEventManager::Button::Right, pt.x, pt.y);
		break;
	case WM_MBUTTONUP:
		mouseEvent.onButtonReleased(MouseEventManager::Button::Middle, pt.x, pt.y);
		break;
	case WM_XBUTTONUP:
		if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) {
			mouseEvent.onButtonReleased(MouseEventManager::Button::Button4, pt.x, pt.y);
		}
		else {
			mouseEvent.onButtonReleased(MouseEventManager::Button::Button5, pt.x, pt.y);
		}
		break;
	case WM_MOUSEWHEEL:
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		mouseEvent.onWheelDelta(pt.x, pt.y, delta);


		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


// Exception Stuff

Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
	: TronException(line, file), hr(hr) {}

const char* Window::Exception::what() const noexcept {
	std::ostringstream oss;
	oss << this->getType() << std::endl
		<< "Error Code : " << this->getErrorCode() << std::endl
		<< "Description :" << this->getDescription() << std::endl
		<< getLocationInString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::Exception::getType() const noexcept {
	return "Tron Window Exception";
}

std::string Window::Exception::translateErrorCode(HRESULT hr) noexcept {
	char* pMsgBuf = nullptr;
	// Ask windows to give us the string version of this error code
	DWORD nMsgLen = FormatMessage(
		// alocate the message         | search from system         | remove the inserting things
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);
	if (nMsgLen == 0) {
		return "Unidentified error code";
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);// FormatMessage uses malloc, so we have to free it
	return errorString;
}

HRESULT Window::Exception::getErrorCode() const noexcept {
	return this->hr;
}

std::string Window::Exception::getDescription() const noexcept {
	return translateErrorCode(this->hr);
}
