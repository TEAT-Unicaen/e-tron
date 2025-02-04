#pragma once 
#include <d3d11.h>
#include <Windows.h> // Assure que HWND est reconnu
#pragma comment(lib, "d3d11.lib")

#include "window.h"

class Renderer {

public:
	Renderer(HWND hwnd, int width, int height);
	~Renderer();
	void render();
	void fill(float r, float g, float b);

private:

	void init(HWND hwnd, int width, int height);

	// Direct3D globals
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;
};