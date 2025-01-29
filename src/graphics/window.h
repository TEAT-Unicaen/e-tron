#pragma once
#include "setUpWindows.h"
#include "resource.h"
#include "keyboardManager.h"
#include "../utils/tronException.h"


class Window {
private:
	class WindowClass {
	public:
		static const char* getName() noexcept;
		static HINSTANCE getInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "E-tron";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	class Exception : public TronException {
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* getType() const noexcept override;
		static std::string translateErrorCode(HRESULT hr) noexcept;
		HRESULT getErrorCode() const noexcept;
		std::string getDescription() const noexcept;
	private:
		HRESULT hr;
	};


	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	void setTitle(const std::string& title);

	KeyboardManager keyEvent;
private:
	static LRESULT CALLBACK handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK handleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	int width;
	int height;
	HWND hWnd;
};

#define WIN_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, hr)