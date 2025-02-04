#pragma once

#include "setUpWindows.h"
#include "resource/resource.h"
#include "event/KeyboardEventManager.h"
#include "event/mouseEventManager.h"
#include "../utils/utils.h"
#include "../utils/tronException.h"
#include "renderer.h"
#include <memory>


#include <optional>

class Renderer;

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


	Window(int width, int height, const char* name, bool handleCloseButton = true);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	void setTitle(const std::string& title);
	Renderer& getRenderer();

	std::optional<int> processMessages() noexcept;

	KeyboardEventManager keyEvent;
	MouseEventManager mouseEvent;

	bool handleCloseButton;
private:
	static LRESULT CALLBACK handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK handleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	int width;
	int height;
	
	HWND hWnd;

	std::unique_ptr<Renderer> renderer;
};

#define WIN_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, hr)