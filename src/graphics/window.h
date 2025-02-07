#pragma once

#include "setUpWindows.h"
#include "resource/resource.h"
#include "event/KeyboardEventManager.h"
#include "event/mouseEventManager.h"
#include "../utils/utils.h"
#include "exception/windowException.h"
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

	std::unique_ptr<Renderer> pRenderer;
};