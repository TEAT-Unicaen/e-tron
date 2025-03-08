#pragma once 
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <wrl.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#pragma comment(lib, "D3dcompiler.lib")

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")
#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")

#include "../../utils/setUpWindows.h" // Assure que HWND est reconnu
#include "../../utils/color.h"
#include "../../objects/camera.h"
#include "../exception/rendererException.h"

namespace Mwrl = Microsoft::WRL;

class Renderer {
	friend class Bindable;
public:
	Renderer(HWND hwnd, int width, int height);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer() = default;

	void render();
	void fill(Color color);
	void drawIndexed(UINT count) noexcept(!IS_DEBUG_MODE);
	dx::XMMATRIX getProjection() const noexcept;
	Camera& getCamera() noexcept;
	dx::XMMATRIX getView()const noexcept;
	void renderText(const std::wstring& text, const dx::XMFLOAT2& position, float size, Color color);
private:
	Camera camera;
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif // !NDEBUG

	// Direct3D globals
	Mwrl::ComPtr<ID3D11Device> pDevice;
	Mwrl::ComPtr<ID3D11DeviceContext> pDeviceContext;
	Mwrl::ComPtr<IDXGISwapChain> pSwapChain;
	Mwrl::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
	Mwrl::ComPtr<ID3D11DepthStencilView> pDepthStencilView;

	// Direct2D/DirectWrite for text rendering
	Mwrl::ComPtr<ID2D1Factory> pD2DFactory;
	Mwrl::ComPtr<IDWriteFactory> pDWriteFactory;
	Mwrl::ComPtr<ID2D1RenderTarget> pD2DRenderTarget;
	Mwrl::ComPtr<IDWriteTextFormat> pTextFormat;
	Mwrl::ComPtr<ID2D1SolidColorBrush> pBrush;
};

// Renderer exception macros
#ifndef NDEBUG // in Debug mode
	#define RENDERER_EXCEPT(hr) RendererHrException(__LINE__, __FILE__, hr, infoManager.getMessages())
	#define RENDERER_LAST_EXCEPT() RENDERER_EXCEPT(GetLastError())
	#define DEVICE_REMOVED_EXCEPT(hr) DeviceRemovedException(__LINE__, __FILE__, hr, infoManager.getMessages())

	#define CHECK_RENDERER_EXCEPT(hrcall) infoManager.updateTheStartingPointIndex(); if (FAILED(hr = (hrcall))) throw RENDERER_EXCEPT(hr)
	#define CHECK_INFO_ONLY_EXCEPT(call) infoManager.updateTheStartingPointIndex(); (call); {auto v = infoManager.getMessages(); if(!v.empty()) {throw INFO_ONLY_EXCEPT(v);}}
#else // in Release mode
	#define RENDERER_EXCEPT(hr) RendererHrException(__LINE__, __FILE__, hr)
	#define RENDERER_LAST_EXCEPT() RENDERER_EXCEPT(GetLastError())
	#define DEVICE_REMOVED_EXCEPT(hr)  DeviceRemovedException(__LINE__, __FILE__, hr)

	#define CHECK_RENDERER_EXCEPT(hrcall) if (FAILED(hr = (hrcall))) throw RENDERER_EXCEPT(hr)
	#define CHECK_INFO_ONLY_EXCEPT(call) call
#endif // !NDEBUG
