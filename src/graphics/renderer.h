#pragma once 
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <wrl.h>

#include "setUpWindows.h" // Assure que HWND est reconnu
#include "exception/rendererException.h"

namespace Mwrl = Microsoft::WRL;

class Renderer {
public:
	Renderer(HWND hwnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer() = default;

	void render();
	void fill(float r, float g, float b);

private:
	// Direct3D globals
	Mwrl::ComPtr<ID3D11Device> pDevice;
	Mwrl::ComPtr<ID3D11DeviceContext> pDeviceContext;
	Mwrl::ComPtr<IDXGISwapChain> pSwapChain;
	Mwrl::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
};
#define HR HRESULT hr
#define CHECK_RENDERER_EXCEPT(hrcall) if (FAILED(hr = (hrcall))) throw RENDERER_EXCEPT(hr)