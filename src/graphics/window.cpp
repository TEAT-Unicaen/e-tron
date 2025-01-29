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
Window::Window(int width, int height, const char* name) {
	RECT wr = {0};
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	if (FAILED(AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE))) {
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
	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
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
